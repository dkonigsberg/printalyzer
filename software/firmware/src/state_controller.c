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
#include "illum_controller.h"
#include "util.h"
#include "settings.h"
#include "state_home.h"
#include "state_timer.h"
#include "state_test_strip.h"

static const char *TAG = "state_controller";

struct __state_controller_t {
    state_identifier_t current_state;
    state_identifier_t next_state;
    exposure_state_t exposure_state;
    TickType_t focus_start_ticks;
};

static state_controller_t state_controller = {0};
static state_t *state_map[STATE_MAX] = {0};

static bool state_add_adjustment_process(state_t *state_base, state_controller_t *controller);
static state_t state_add_adjustment_data = {
    .state_process = state_add_adjustment_process
};

static bool state_menu_process(state_t *state_base, state_controller_t *controller);
static state_t state_menu_data = {
    .state_process = state_menu_process
};

void state_controller_init()
{
    state_controller.current_state = STATE_MAX;
    state_controller.next_state = STATE_HOME;
    exposure_state_defaults(&(state_controller.exposure_state));
    state_controller.focus_start_ticks = 0;

    state_map[STATE_HOME] = state_home();
    state_map[STATE_HOME_CHANGE_TIME_INCREMENT] = state_home_change_time_increment();
    state_map[STATE_HOME_ADJUST_FINE] = state_home_adjust_fine();
    state_map[STATE_HOME_ADJUST_ABSOLUTE] = state_home_adjust_absolute();
    state_map[STATE_TIMER] = state_timer();
    state_map[STATE_TEST_STRIP] = state_test_strip();
    state_map[STATE_ADD_ADJUSTMENT] = &state_add_adjustment_data;
    state_map[STATE_MENU] = &state_menu_data;
}

void state_controller_loop()
{
    state_t *state = NULL;
    for (;;) {
        // Check if we need to do a state transition
        if (state_controller.next_state != state_controller.current_state) {
            // Transition to the new state
            ESP_LOGI(TAG, "State transition: %d -> %d", state_controller.current_state, state_controller.next_state);
            state_controller.current_state = state_controller.next_state;

            if (state_controller.current_state < STATE_MAX && state_map[state_controller.current_state]) {
                state = state_map[state_controller.current_state];
            } else {
                state = NULL;
            }

            // Call the state entry function
            if (state && state->state_entry) {
                state->state_entry(state, &state_controller);
            }
        }

        // Call the process function for the state
        if (state && state->state_process) {
            bool result = state->state_process(state, &state_controller);

            // Reset inactivity timeouts as necessary
            if (result) {
                if (relay_enlarger_is_enabled()) {
                    state_controller_start_focus_timeout(&state_controller);
                }
            }
        }

        // Handle behaviors resulting from inactivity timeouts
        TickType_t max_focus_ticks = pdMS_TO_TICKS(settings_get_enlarger_focus_timeout());
        if (relay_enlarger_is_enabled() && (xTaskGetTickCount() - state_controller.focus_start_ticks) >= max_focus_ticks) {
            ESP_LOGI(TAG, "Focus mode disabled due to timeout");
            relay_enlarger_enable(false);
            illum_controller_safelight_state(ILLUM_SAFELIGHT_HOME);
            state_controller.focus_start_ticks = 0;
        }

        // Check if we will do a state transition on the next loop
        if (state_controller.next_state != state_controller.current_state) {
            if (state && state->state_exit) {
                state->state_exit(state, &state_controller);
            }
        }
    }
}

void state_controller_set_next_state(state_controller_t *controller, state_identifier_t next_state)
{
    if (!controller) { return; }
    controller->next_state = next_state;
}

state_identifier_t state_controller_get_next_state(state_controller_t *controller)
{
    if (!controller) { return STATE_MAX; }
    return controller->next_state;
}

exposure_state_t *state_controller_get_exposure_state(state_controller_t *controller)
{
    if (!controller) { return NULL; }
    return &(controller->exposure_state);
}

void state_controller_start_focus_timeout(state_controller_t *controller)
{
    if (!controller) { return; }
    controller->focus_start_ticks = xTaskGetTickCount();
}

void state_controller_stop_focus_timeout(state_controller_t *controller)
{
    if (!controller) { return; }
    controller->focus_start_ticks = 0;
}

bool state_add_adjustment_process(state_t *state_base, state_controller_t *controller)
{
    //TODO This is just a placeholder until the feature is implemented
    state_controller_set_next_state(controller, STATE_HOME);
    return true;
}

bool state_menu_process(state_t *state_base, state_controller_t *controller)
{
    // Because of how u8g2 menu functions are designed, it is simply easier
    // to just implement the menu system as a tree of simple function calls.
    // As such, the menu system is simply hooked in this way and doesn't
    // really participate in the main state machine.
    main_menu_start();
    state_controller_set_next_state(controller, STATE_HOME);
    return true;
}
