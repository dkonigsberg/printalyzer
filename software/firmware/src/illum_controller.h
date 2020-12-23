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

void illum_controller_safelight_state(illum_safelight_t mode);

void illum_controller_blackout_state(bool enabled);

#endif /* ILLUM_CONTROLLER_H */
