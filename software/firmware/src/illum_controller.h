/*
 * Illumination Controller
 *
 * Responsible for managing the actual on/off control of any part
 * of the device that emits light, with the exception of the
 * enlarger relay.
 * This includes the safelight relay, the display lighting,
 * and the panel LEDs.
 */

#ifndef ILLUM_CONTROLLER_H
#define ILLUM_CONTROLLER_H

#include <stdbool.h>

typedef enum {
    ILLUM_SAFELIGHT_HOME = 0,
    ILLUM_SAFELIGHT_FOCUS,
    ILLUM_SAFELIGHT_EXPOSURE,
    ILLUM_SAFELIGHT_MEASUREMENT,
} illum_safelight_t;

void illum_controller_init();

void illum_controller_safelight_state(illum_safelight_t mode);

bool illum_controller_is_blackout();

/**
 * Enable or disable screenshot mode.
 *
 * In screenshot mode, the blackout switch will trigger display screenshots
 * instead of turning off device illumination. It is being placed here
 * because this module is otherwise responsible for all blackout behaviors.
 */
void illum_controller_set_screenshot_mode(bool enabled);

/**
 * Get whether screenshot mode is enabled.
 */
bool illum_controller_get_screenshot_mode();

void illum_controller_keypad_blackout_callback(bool enabled, void *user_data);

#endif /* ILLUM_CONTROLLER_H */
