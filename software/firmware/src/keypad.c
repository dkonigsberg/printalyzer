#include "keypad.h"

#include <stm32f4xx_hal.h>
#include <FreeRTOS.h>
#include <queue.h>
#include <timers.h>
#include <cmsis_os.h>

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include <esp_log.h>

#include "tca8418.h"

static const char *TAG = "keypad";

#define KEYPAD_INDEX_MAX       14
#define KEYPAD_REPEAT_DELAY_MS 600
#define KEYPAD_REPEAT_RATE_S   25

/* Internal raw keypad event data */
typedef struct {
    keypad_key_t keycode;
    bool pressed;
    TickType_t ticks;
    bool repeated;
} keypad_raw_event_t;

/* Handle to I2C peripheral used by the keypad controller */
static I2C_HandleTypeDef *keypad_i2c;

/* Task to handle raw keypad events */
static osThreadId_t keypad_task_handle;
const osThreadAttr_t keypad_task_attributes = {
    .name = "keypad_task",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 2048
};

/* Queue for raw keypad events, which come from the controller or timers */
static QueueHandle_t keypad_raw_event_queue = NULL;

/* Queue for emitted keypad events, which are handled by the application */
static QueueHandle_t keypad_event_queue = NULL;

/* Currently known state of all keypad buttons */
static uint16_t button_state;

/* Timer for button repeat events */
static TimerHandle_t button_repeat_timer;

/* Whether timer is in initial delay or repeating event mode */
static UBaseType_t button_repeat_timer_reload;

/* Flag to prevent duplicate initialization */
static bool keypad_initialized = false;

static void keypad_task(void *argument);
static void keypad_handle_key_event(uint8_t keycode, bool pressed, TickType_t ticks);
static void keypad_handle_key_repeat(uint8_t keycode, TickType_t ticks);
static void keypad_button_repeat_timer_callback(TimerHandle_t xTimer);
static uint8_t keypad_keycode_to_index(keypad_key_t keycode);
static bool keypad_keycode_can_repeat(keypad_key_t keycode);

HAL_StatusTypeDef keypad_init(I2C_HandleTypeDef *hi2c)
{
    HAL_StatusTypeDef ret = HAL_OK;

    if (keypad_initialized) {
        ESP_LOGE(TAG, "Keypad controller already initialized");
        return HAL_OK;
    }
    if (!hi2c) {
        return HAL_ERROR;
    }

    ESP_LOGI(TAG, "Initializing keypad controller");

    keypad_i2c = hi2c;

    // Create the queues for key events
    keypad_raw_event_queue = xQueueCreate(20, sizeof(keypad_raw_event_t));
    if (!keypad_raw_event_queue) {
        return HAL_ERROR;
    }

    keypad_event_queue = xQueueCreate(20, sizeof(keypad_event_t));
    if (!keypad_event_queue) {
        return HAL_ERROR;
    }

    // Clear the button state
    button_state = 0;

    // Create the timer to handle key repeat events
    button_repeat_timer = xTimerCreate(
        "keypad_repeat", 1, pdFALSE, ( void * ) 0,
        keypad_button_repeat_timer_callback);
    button_repeat_timer_reload = pdFALSE;

    // Create the task to process keypad events
    keypad_task_handle = osThreadNew(keypad_task, NULL, &keypad_task_attributes);

    // Initialize the keypad controller
    do {
        if ((ret = tca8418_init(keypad_i2c)) != HAL_OK) {
            break;
        }

        const tca8418_pins_t pins_zero = { 0x00, 0x00, 0x00 };
        const tca8418_pins_t pins_int = { 0x0F, 0xFF, 0x03 };

        // Enable pull-ups on all GPIO pins
        if ((ret = tca8418_gpio_pullup_disable(keypad_i2c, &pins_zero)) != HAL_OK) {
            break;
        }

        // Set pins to GPIO mode
        if ((ret = tca8418_kp_gpio_select(keypad_i2c, &pins_zero)) != HAL_OK) {
            break;
        }

        // Set the event FIFO (disabled for now)
        if ((ret = tca8418_gpi_event_mode(keypad_i2c, &pins_int)) != HAL_OK) {
            break;
        }

        // Set GPIO direction to input
        if ((ret = tca8418_gpio_data_direction(keypad_i2c, &pins_zero)) != HAL_OK) {
            break;
        }

        // Enable GPIO interrupts
        if ((ret = tca8418_gpio_interrupt_enable(keypad_i2c, &pins_int)) != HAL_OK) {
            break;
        }

        // Set the configuration register to enable GPIO interrupts
        if ((ret = tca8148_set_config(keypad_i2c, TCA8418_CFG_KE_IEN)) != HAL_OK) {
            break;
        }
    } while (0);

    if (ret != HAL_OK) {
        ESP_LOGE(TAG, "Keypad setup error: %d", ret);
        return ret;
    }

    keypad_initialized = true;
    ESP_LOGI(TAG, "Keypad controller initialized");

    return HAL_OK;
}

HAL_StatusTypeDef keypad_inject_event(const keypad_event_t *event)
{
    if (!event) {
        return HAL_ERROR;
    }

    xQueueSend(keypad_event_queue, event, 0);
    return HAL_OK;
}

HAL_StatusTypeDef keypad_clear_events()
{
    xQueueReset(keypad_event_queue);
    return HAL_OK;
}

HAL_StatusTypeDef keypad_flush_events()
{
    keypad_event_t event;
    bzero(&event, sizeof(keypad_event_t));
    xQueueReset(keypad_event_queue);
    xQueueSend(keypad_event_queue, &event, 0);
    return HAL_OK;
}

HAL_StatusTypeDef keypad_wait_for_event(keypad_event_t *event, int msecs_to_wait)
{
    TickType_t ticks = msecs_to_wait < 0 ? portMAX_DELAY : (msecs_to_wait / portTICK_RATE_MS);
    if (!xQueueReceive(keypad_event_queue, event, ticks)) {
        if (msecs_to_wait > 0) {
            return HAL_TIMEOUT;
        } else {
            bzero(event, sizeof(keypad_event_t));
        }
    }
    return HAL_OK;
}

HAL_StatusTypeDef keypad_int_event_handler()
{
    HAL_StatusTypeDef ret = HAL_OK;
    TickType_t ticks = xTaskGetTickCount();

    if (!keypad_initialized) {
        return ret;
    }

    do {
        uint8_t int_status;

        // Read the INT_STAT (0x02) register to determine what asserted the
        // INT line. If GPI_INT or K_INT is set, then  a key event has
        // occurred, and the event is stored in the FIFO.
        ret = tca8148_get_interrupt_status(keypad_i2c, &int_status);
        if (ret != HAL_OK) {
            break;
        }
        ESP_LOGD(TAG, "INT_STAT: %02X (GPI=%d, K=%d)", int_status,
                (int_status & TCA8418_INT_STAT_GPI_INT) != 0,
                (int_status & TCA8418_INT_STAT_K_INT) != 0);

        // Read the KEY_LCK_EC (0x03) register, bits [3:0] to see how many
        // events are stored in FIFO.
        uint8_t count;
        ret = tca8148_get_key_event_count(keypad_i2c, &count);
        if (ret != HAL_OK) {
            break;
        }
        ESP_LOGD(TAG, "Key event count: %d", count);

        bool key_error = false;
        bool cb_error = false;
        do {
            uint8_t keycode;
            bool pressed;
            ret = tca8148_get_next_key_event(keypad_i2c, &keycode, &pressed);
            if (ret != HAL_OK) {
                key_error = true;
                break;
            }

            if (keycode == 0 && pressed == 0) {
                // Last key has been read, break the loop
                break;
            }

            // Send the raw event to the queue used by the keypad
            // event processing task
            keypad_raw_event_t raw_event = {
                .keycode = keycode,
                .pressed = pressed,
                .ticks = ticks,
                .repeated = false
            };
            xQueueSend(keypad_raw_event_queue, &raw_event, 0);
        } while (!key_error && !cb_error);

        if (key_error) {
            break;
        }

        // Read the GPIO INT STAT registers
        tca8418_pins_t int_pins;
        ret = tca8148_get_gpio_interrupt_status(keypad_i2c, &int_pins);
        if (ret != HAL_OK) {
            break;
        }
        ESP_LOGD(TAG, "GPIO_INT_STAT: %02X %02X %02X", int_pins.rows, int_pins.cols_l, int_pins.cols_h);

        // Reset the INT_STAT interrupt flag which was causing the interrupt
        // by writing a 1 to the specific bit.
        ret = tca8148_set_interrupt_status(keypad_i2c, int_status);
        if (ret != HAL_OK) {
            break;
        }
    } while (0);
    return ret;
}

void keypad_task(void *argument)
{
    keypad_raw_event_t raw_event;
    for (;;) {
        if(xQueueReceive(keypad_raw_event_queue, &raw_event, portMAX_DELAY)) {
            if (!raw_event.repeated) {
                keypad_handle_key_event(raw_event.keycode, raw_event.pressed, raw_event.ticks);
            } else {
                keypad_handle_key_repeat(raw_event.keycode, raw_event.ticks);
            }
        }
    }
}

void keypad_handle_key_event(uint8_t keycode, bool pressed, TickType_t ticks)
{
    // Update the button state information
    TickType_t tick_duration = 0;
    uint8_t index = keypad_keycode_to_index(keycode);
    if (index < KEYPAD_INDEX_MAX) {
        uint16_t mask = 1 << index;
        if (pressed) {
            button_state |= mask;
        } else {
            button_state &= ~mask;
        }
    }

    // Limit the max duration we can report
    if (tick_duration > UINT16_MAX) {
        tick_duration = UINT16_MAX;
    }

    // Handle keys that can repeat
    if (keypad_keycode_can_repeat(keycode)) {
        if (pressed) {
            // Pressing a repeatable key should reset and restart the
            // repeat timer.
            if (xTimerIsTimerActive(button_repeat_timer) == pdTRUE) {
                xTimerStop(button_repeat_timer, portMAX_DELAY);
            }

            uint32_t keycode_id = keycode;
            xTimerChangePeriod(button_repeat_timer, pdMS_TO_TICKS(KEYPAD_REPEAT_DELAY_MS), portMAX_DELAY);
            vTimerSetReloadMode(button_repeat_timer, pdFALSE);
            button_repeat_timer_reload = pdFALSE;
            vTimerSetTimerID(button_repeat_timer, (void *)keycode_id);
            xTimerStart(button_repeat_timer, portMAX_DELAY);
        } else {
            // Releasing a repeatable key should stop the repeat timer
            if (xTimerIsTimerActive(button_repeat_timer) == pdTRUE) {
                xTimerStop(button_repeat_timer, portMAX_DELAY);
            }
        }
    }

    // Generate the keypad event
    keypad_event_t keypad_event = {
        .key = keycode,
        .pressed = pressed,
        .repeated = false,
        .keypad_state = button_state
    };
    ESP_LOGI(TAG, "Key event: key=%d, pressed=%d, state=%04X", keycode, pressed, button_state);

    xQueueSend(keypad_event_queue, &keypad_event, 0);
}

void keypad_handle_key_repeat(uint8_t keycode, TickType_t ticks)
{
    // Make sure the repeated key is still pressed, and shortcut out if
    // it is not.
    int index = keypad_keycode_to_index(keycode);
    if (index < KEYPAD_INDEX_MAX && !(button_state & (1 << index))) {
        xTimerStop(button_repeat_timer, portMAX_DELAY);
        return;
    }

    if (button_repeat_timer_reload == pdFALSE) {
        // The initial period elapsed, so reconfigure for key repeat
        xTimerStop(button_repeat_timer, portMAX_DELAY);
        xTimerChangePeriod(button_repeat_timer, pdMS_TO_TICKS(1000) / KEYPAD_REPEAT_RATE_S, portMAX_DELAY);
        vTimerSetReloadMode(button_repeat_timer, pdTRUE);
        button_repeat_timer_reload = pdTRUE;
        xTimerStart(button_repeat_timer, portMAX_DELAY);
    }

    // Generate the keypad event
    keypad_event_t keypad_event = {
        .key = keycode,
        .pressed = true,
        .repeated = true,
        .keypad_state = button_state
    };
    ESP_LOGI(TAG, "Key event: key=%d, pressed=1, state=%04X (repeat)", keycode, button_state);

    xQueueSend(keypad_event_queue, &keypad_event, 0);
}

void keypad_button_repeat_timer_callback(TimerHandle_t xTimer)
{
    TickType_t ticks = xTaskGetTickCount();
    uint32_t keycode_id = (uint32_t)pvTimerGetTimerID(xTimer);

    keypad_raw_event_t raw_event = {
        .keycode = (uint16_t)keycode_id,
        .pressed = true,
        .ticks = ticks,
        .repeated = true
    };
    xQueueSend(keypad_raw_event_queue, &raw_event, 0);
}

bool keypad_is_key_pressed(const keypad_event_t *event, keypad_key_t key)
{
    int index = keypad_keycode_to_index(key);
    if (index < KEYPAD_INDEX_MAX && event && event->keypad_state & (1 << index)) {
        return true;
    } else {
        return false;
    }
}

uint8_t keypad_keycode_to_index(keypad_key_t keycode)
{
    switch (keycode) {
    case KEYPAD_START:
        return 0;
    case KEYPAD_FOCUS:
        return 1;
    case KEYPAD_INC_EXPOSURE:
        return 2;
    case KEYPAD_DEC_EXPOSURE:
        return 3;
    case KEYPAD_INC_CONTRAST:
        return 4;
    case KEYPAD_DEC_CONTRAST:
        return 5;
    case KEYPAD_ADD_ADJUSTMENT:
        return 6;
    case KEYPAD_TEST_STRIP:
        return 7;
    case KEYPAD_CANCEL:
        return 8;
    case KEYPAD_MENU:
        return 9;
    case KEYPAD_ENCODER:
        return 10;
    case KEYPAD_BLACKOUT:
        return 11;
    case KEYPAD_FOOTSWITCH:
        return 12;
    case KEYPAD_METER_PROBE:
        return 13;
    default:
        return KEYPAD_INDEX_MAX;
    }
}

bool keypad_keycode_can_repeat(keypad_key_t keycode)
{
    switch (keycode) {
    case KEYPAD_START:
    case KEYPAD_FOCUS:
    case KEYPAD_INC_EXPOSURE:
    case KEYPAD_DEC_EXPOSURE:
    case KEYPAD_INC_CONTRAST:
    case KEYPAD_DEC_CONTRAST:
    case KEYPAD_ADD_ADJUSTMENT:
    case KEYPAD_TEST_STRIP:
    case KEYPAD_CANCEL:
    case KEYPAD_MENU:
    case KEYPAD_ENCODER:
    case KEYPAD_METER_PROBE:
        return true;
    case KEYPAD_BLACKOUT:
    case KEYPAD_FOOTSWITCH:
    default:
        return false;
    }
}
