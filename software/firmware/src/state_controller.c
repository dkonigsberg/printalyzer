#include "state_controller.h"

#include <FreeRTOS.h>
#include <cmsis_os.h>
#include <task.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <esp_log.h>

#include "keypad.h"
#include "display.h"
#include "exposure_state.h"
#include "main_menu.h"
#include "buzzer.h"
#include "led.h"
#include "relay.h"
#include "exposure_timer.h"
#include "enlarger_profile.h"
#include "util.h"
#include "settings.h"

static const char *TAG = "state_controller";

typedef enum {
    STATE_HOME,
    STATE_HOME_CHANGE_TIME_INCREMENT,
    STATE_TIMER,
    STATE_TEST_STRIP,
    STATE_ADD_ADJUSTMENT,
    STATE_MENU
} state_identifier_t;

typedef struct {
    bool change_inc_pending;
    bool change_inc_swallow_release_up;
    bool change_inc_swallow_release_down;
    int cancel_repeat;
    bool display_dirty;
} state_home_data_t;

/* State data used by the home screen and related screens */
exposure_state_t exposure_state;

static TickType_t focus_start_ticks;

void state_home_init(state_home_data_t *state_data);
static state_identifier_t state_home(state_home_data_t *state_data);

static state_identifier_t state_home_change_time_increment();
static state_identifier_t state_timer();
static state_identifier_t state_test_strip();
static bool state_test_strip_countdown(uint32_t patch_time_ms, bool last_patch);
static state_identifier_t state_add_adjustment();
static state_identifier_t state_menu();

void state_controller_init()
{
    exposure_state_defaults(&exposure_state);
    focus_start_ticks = 0;
}

void state_controller_loop()
{
    // State data initialization
    state_home_data_t home_data;
    state_home_init(&home_data);

    state_identifier_t current_state = STATE_HOME;
    state_identifier_t next_state = current_state;
    for (;;) {
        switch (current_state) {
        case STATE_HOME:
            next_state = state_home(&home_data);
            break;
        case STATE_HOME_CHANGE_TIME_INCREMENT:
            next_state = state_home_change_time_increment();
            break;
        case STATE_TIMER:
            next_state = state_timer();
            break;
        case STATE_TEST_STRIP:
            next_state = state_test_strip();
            break;
        case STATE_ADD_ADJUSTMENT:
            next_state = state_add_adjustment();
            break;
        case STATE_MENU:
            next_state = state_menu();
            break;
        default:
            break;
        }

        TickType_t max_focus_ticks = pdMS_TO_TICKS(settings_get_enlarger_focus_timeout());
        if (relay_enlarger_is_enabled() && (xTaskGetTickCount() - focus_start_ticks) >= max_focus_ticks) {
            ESP_LOGI(TAG, "Focus mode disabled due to timeout");
            relay_enlarger_enable(false);
            focus_start_ticks = 0;
        }

        if (next_state != current_state) {
            ESP_LOGI(TAG, "State transition: %d -> %d", current_state, next_state);
            current_state = next_state;
        }
    }
}

void state_home_init(state_home_data_t *state_data)
{
    state_data->change_inc_pending = false;
    state_data->change_inc_swallow_release_up = false;
    state_data->change_inc_swallow_release_down = false;
    state_data->cancel_repeat = 0;
    state_data->display_dirty = true;
}

state_identifier_t state_home(state_home_data_t *state_data)
{
    state_identifier_t next_state = STATE_HOME;

    if (state_data->display_dirty) {
        // Draw current exposure state
        display_main_elements_t main_elements;
        convert_exposure_to_display(&main_elements, &exposure_state);
        display_draw_main_elements(&main_elements);
        state_data->display_dirty = false;
    }

    // Handle the next keypad event
    keypad_event_t keypad_event;
    if (keypad_wait_for_event(&keypad_event, 200) == HAL_OK) {
        if (state_data->change_inc_pending) {
            if (keypad_event.key == KEYPAD_INC_EXPOSURE && !keypad_event.pressed) {
                state_data->change_inc_swallow_release_up = false;
            } else if (keypad_event.key == KEYPAD_DEC_EXPOSURE && !keypad_event.pressed) {
                state_data->change_inc_swallow_release_down = false;
            }

            if (!state_data->change_inc_swallow_release_up && !state_data->change_inc_swallow_release_down) {
                state_data->change_inc_pending = false;
                next_state = STATE_HOME_CHANGE_TIME_INCREMENT;
            }
        } else {
            if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_START)) {
                next_state = STATE_TIMER;
            } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_FOCUS)) {
                if (!relay_enlarger_is_enabled()) {
                    ESP_LOGI(TAG, "Focus mode enabled");
                    relay_enlarger_enable(true);
                    focus_start_ticks = xTaskGetTickCount();
                } else {
                    ESP_LOGI(TAG, "Focus mode disabled");
                    relay_enlarger_enable(false);
                    focus_start_ticks = 0;
                }
            } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_INC_EXPOSURE)) {
                exposure_adj_increase(&exposure_state);
                state_data->display_dirty = true;
            } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_DEC_EXPOSURE)) {
                exposure_adj_decrease(&exposure_state);
                state_data->display_dirty = true;
            } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_INC_CONTRAST)) {
                exposure_contrast_increase(&exposure_state);
                state_data->display_dirty = true;
            } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_DEC_CONTRAST)) {
                exposure_contrast_decrease(&exposure_state);
                state_data->display_dirty = true;
            } else if (keypad_event.key == KEYPAD_TEST_STRIP && !keypad_event.pressed) {
                next_state = STATE_TEST_STRIP;
            } else if (keypad_event.key == KEYPAD_MENU && !keypad_event.pressed) {
                next_state = STATE_MENU;
            } else if (keypad_event.key == KEYPAD_CANCEL) {
                if (keypad_event.pressed || keypad_event.repeated) {
                    state_data->cancel_repeat++;
                } else {
                    if (state_data->cancel_repeat > 2) {
                        exposure_state_defaults(&exposure_state);
                        state_data->display_dirty = true;
                    }
                    state_data->cancel_repeat = 0;
                }
            } else if (keypad_is_key_combo_pressed(&keypad_event, KEYPAD_INC_EXPOSURE, KEYPAD_DEC_EXPOSURE)) {
                state_data->change_inc_pending = true;
                state_data->change_inc_swallow_release_up = true;
                state_data->change_inc_swallow_release_down = true;
            }
        }

        // Key events should reset the focus timeout
        if (relay_enlarger_is_enabled()) {
            focus_start_ticks = xTaskGetTickCount();
        }
    }

    if (next_state != STATE_HOME
        && next_state != STATE_HOME_CHANGE_TIME_INCREMENT
        && next_state != STATE_ADD_ADJUSTMENT) {
        if (relay_enlarger_is_enabled()) {
            ESP_LOGI(TAG, "Focus mode disabled due to state change");
            relay_enlarger_enable(false);
            focus_start_ticks = 0;
        }
    }

    if (next_state != STATE_HOME) {
        state_data->display_dirty = true;
    }

    return next_state;
}

state_identifier_t state_home_change_time_increment()
{
    state_identifier_t next_state = STATE_HOME_CHANGE_TIME_INCREMENT;

    // Draw current stop increment
    uint8_t stop_inc_den = exposure_adj_increment_get_denominator(&exposure_state);
    display_draw_stop_increment(stop_inc_den);

    // Handle the next keypad event
    keypad_event_t keypad_event;
    if (keypad_wait_for_event(&keypad_event, 200) == HAL_OK) {
        if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_INC_EXPOSURE)) {
            exposure_adj_increment_increase(&exposure_state);
        } else if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_DEC_EXPOSURE)) {
            exposure_adj_increment_decrease(&exposure_state);
        } else if (keypad_event.key == KEYPAD_CANCEL && !keypad_event.pressed) {
            next_state = STATE_HOME;
        }

        // Key events should reset the focus timeout
        if (relay_enlarger_is_enabled()) {
            focus_start_ticks = xTaskGetTickCount();
        }
    }

    return next_state;
}

static bool state_timer_exposure_callback(exposure_timer_state_t state, uint32_t time_ms, void *user_data)
{
    display_exposure_timer_t *elements = user_data;
    display_exposure_timer_t prev_elements;

    memcpy(&prev_elements, elements, sizeof(display_exposure_timer_t));

    update_display_timer(elements, time_ms);
    display_draw_exposure_timer(elements, &prev_elements);

    // Handle the next keypad event without blocking
    keypad_event_t keypad_event;
    if (keypad_wait_for_event(&keypad_event, 0) == HAL_OK) {
        if (keypad_event.key == KEYPAD_CANCEL && !keypad_event.pressed) {
            ESP_LOGI(TAG, "Canceling exposure timer at %ldms", time_ms);
            return false;
        }
    }

    return true;
}

state_identifier_t state_timer()
{
    state_identifier_t next_state = STATE_HOME;

    uint32_t exposure_time_ms = rounded_exposure_time_ms(exposure_state.adjusted_time);

    display_exposure_timer_t elements;
    convert_exposure_to_display_timer(&elements, exposure_time_ms);

    exposure_timer_config_t timer_config = {0};
    timer_config.end_tone = EXPOSURE_TIMER_END_TONE_REGULAR;
    timer_config.timer_callback = state_timer_exposure_callback;
    timer_config.user_data = &elements;

    if (elements.fraction_digits == 0) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_1_SEC;
    } else if (elements.fraction_digits == 1) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_100_MS;
    } else if (elements.fraction_digits == 2) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_10_MS;
    } else {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_1_SEC;
    }

    const enlarger_profile_t *enlarger_profile = settings_get_default_enlarger_profile();
    exposure_timer_set_config_time(&timer_config, exposure_time_ms, enlarger_profile);

    exposure_timer_set_config(&timer_config);

    ESP_LOGI(TAG, "Starting exposure timer for %ldms", exposure_time_ms);

    display_draw_exposure_timer(&elements, 0);

    //TODO turn off the safelight relay (if not in blackout)

    HAL_StatusTypeDef ret = exposure_timer_run();
    if (ret == HAL_TIMEOUT) {
        ESP_LOGE(TAG, "Exposure timer canceled");
    } else if (ret != HAL_OK) {
        ESP_LOGE(TAG, "Exposure timer error");
    }

    ESP_LOGI(TAG, "Exposure timer complete");

    //TODO turn on the safelight relay (if not in blackout)

    return next_state;
}

state_identifier_t state_test_strip()
{
    state_identifier_t next_state = STATE_TEST_STRIP;

    buzzer_volume_t current_volume = buzzer_get_volume();
    pam8904e_freq_t current_frequency = buzzer_get_frequency();
    led_set_on(LED_IND_TEST_STRIP);

    int exposure_patch_min;
    unsigned int exposure_patch_count;

    display_test_strip_elements_t elements = {0};
    elements.title1 = "Test Strip";
    elements.time_elements.time_seconds = 25;
    elements.time_elements.time_milliseconds = 1;
    elements.time_elements.fraction_digits = 1;

    switch (exposure_state.adjustment_increment) {
    case EXPOSURE_ADJ_TWELFTH:
        elements.title2 = "1/24 Stop";
        break;
    case EXPOSURE_ADJ_SIXTH:
        elements.title2 = "1/6 Stop";
        break;
    case EXPOSURE_ADJ_QUARTER:
        elements.title2 = "1/4 Stop";
        break;
    case EXPOSURE_ADJ_THIRD:
        elements.title2 = "1/3 Stop";
        break;
    case EXPOSURE_ADJ_HALF:
        elements.title2 = "1/2 Stop";
        break;
    case EXPOSURE_ADJ_WHOLE:
        elements.title2 = "1 Stop";
        break;
    }

    switch (settings_get_teststrip_patches()) {
    case TESTSTRIP_PATCHES_5:
        exposure_patch_min = -2;
        exposure_patch_count = 5;
        elements.patches = DISPLAY_PATCHES_5;
        break;
    case TESTSTRIP_PATCHES_7:
    default:
        exposure_patch_min = -3;
        exposure_patch_count = 7;
        elements.patches = DISPLAY_PATCHES_7;
        break;
    }

    teststrip_mode_t teststrip_mode = settings_get_teststrip_mode();

    //TODO turn off the safelight relay (if not in blackout)

    unsigned int patches_covered = 0;
    do {
        float patch_time;
        if (teststrip_mode == TESTSTRIP_MODE_SEPARATE) {
            patch_time = exposure_get_test_strip_time_complete(&exposure_state, exposure_patch_min + patches_covered);

            elements.covered_patches = 0xFF;
            elements.covered_patches ^= (1 << (exposure_patch_count - patches_covered - 1));
        } else {
            patch_time = exposure_get_test_strip_time_incremental(&exposure_state, exposure_patch_min, patches_covered);

            elements.covered_patches = 0;
            for (int i = 0; i < patches_covered; i++) {
                elements.covered_patches |= (1 << (exposure_patch_count - i - 1));
            }
        }
        uint32_t patch_time_ms = rounded_exposure_time_ms(patch_time);

        convert_exposure_to_display_timer(&(elements.time_elements), patch_time_ms);

        display_draw_test_strip_elements(&elements);

        keypad_event_t keypad_event;
        if (keypad_wait_for_event(&keypad_event, -1) == HAL_OK) {
            if (keypad_is_key_released_or_repeated(&keypad_event, KEYPAD_START)) {
                if (state_test_strip_countdown(patch_time_ms, patches_covered == (exposure_patch_count - 1))) {
                    if (patches_covered < exposure_patch_count) {
                        patches_covered++;
                    }
                } else {
                    next_state = STATE_HOME;
                }
            } else if (keypad_event.key == KEYPAD_CANCEL && !keypad_event.pressed) {
                next_state = STATE_HOME;
            }
        }
    } while (next_state == STATE_TEST_STRIP && patches_covered < exposure_patch_count);

    if (next_state == STATE_TEST_STRIP && patches_covered == exposure_patch_count) {
        osDelay(pdMS_TO_TICKS(500));
        next_state = STATE_HOME;
    }

    //TODO turn on the safelight relay (if not in blackout)

    led_set_off(LED_IND_TEST_STRIP);
    buzzer_set_volume(current_volume);
    buzzer_set_frequency(current_frequency);

    return STATE_HOME;
}

static bool state_test_strip_exposure_callback(exposure_timer_state_t state, uint32_t time_ms, void *user_data)
{
    display_exposure_timer_t *elements = user_data;

    update_display_timer(elements, time_ms);
    display_draw_test_strip_timer(elements);

    // Handle the next keypad event without blocking
    keypad_event_t keypad_event;
    if (keypad_wait_for_event(&keypad_event, 0) == HAL_OK) {
        if (keypad_event.key == KEYPAD_CANCEL && !keypad_event.pressed) {
            ESP_LOGI(TAG, "Canceling test strip timer at %ldms", time_ms);
            return false;
        }
    }

    return true;
}

bool state_test_strip_countdown(uint32_t patch_time_ms, bool last_patch)
{
    display_exposure_timer_t elements;
    convert_exposure_to_display_timer(&elements, patch_time_ms);

    exposure_timer_config_t timer_config = {0};
    timer_config.end_tone = last_patch ? EXPOSURE_TIMER_END_TONE_REGULAR : EXPOSURE_TIMER_END_TONE_SHORT;
    timer_config.timer_callback = state_test_strip_exposure_callback;
    timer_config.user_data = &elements;

    if (elements.fraction_digits == 0) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_1_SEC;
    } else if (elements.fraction_digits == 1) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_100_MS;
    } else if (elements.fraction_digits == 2) {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_10_MS;
    } else {
        timer_config.callback_rate = EXPOSURE_TIMER_RATE_1_SEC;
    }

    const enlarger_profile_t *enlarger_profile = settings_get_default_enlarger_profile();
    exposure_timer_set_config_time(&timer_config, patch_time_ms, enlarger_profile);

    exposure_timer_set_config(&timer_config);

    display_draw_test_strip_timer(&elements);

    HAL_StatusTypeDef ret = exposure_timer_run();
    if (ret == HAL_TIMEOUT) {
        ESP_LOGE(TAG, "Exposure timer canceled");
    } else if (ret != HAL_OK) {
        ESP_LOGE(TAG, "Exposure timer error");
    }

    ESP_LOGI(TAG, "Exposure timer complete");

    return ret == HAL_OK;
}

state_identifier_t state_add_adjustment()
{
    //TODO
    return STATE_HOME;
}

state_identifier_t state_menu()
{
    main_menu_start();
    return STATE_HOME;
}
