#include "exposure_state.h"

#include <math.h>

#include "settings.h"

static void exposure_recalculate(exposure_state_t *state);

void exposure_state_defaults(exposure_state_t *state)
{
    if (!state) { return; }
    state->contrast_grade = settings_get_default_contrast_grade();
    state->base_time = settings_get_default_exposure_time() / 1000.0f;
    state->adjusted_time = state->base_time;
    state->adjustment_value = 0;
    state->adjustment_increment = settings_get_default_step_size();
}

void exposure_set_base_time(exposure_state_t *state, float value)
{
    if (!state) { return; }

    if (value < 0.01f) {
        value = 0.01f;
    } else if (value > 999.0f) {
        value = 999.0f;
    }

    state->base_time = value;
    state->adjustment_value = 0;
    exposure_recalculate(state);
}

void exposure_adj_increase(exposure_state_t *state)
{
    if (!state) { return; }

    /* Clamp adjustment at +/- 12 stops */
    if (state->adjustment_value >= 144) { return; }

    /* Prevent adjusted times beyond 999 seconds */
    if (state->adjusted_time >= 999.0f) { return; }

    state->adjustment_value += state->adjustment_increment;
    exposure_recalculate(state);
}

void exposure_adj_decrease(exposure_state_t *state)
{
    if (!state) { return; }

    /* Clamp adjustment at +/- 12 stops */
    if (state->adjustment_value <= -144) { return; }

    /* Prevent adjusted times below 0.01 seconds */
    if (state->adjusted_time <= 0.01f) { return; }

    state->adjustment_value -= state->adjustment_increment;
    exposure_recalculate(state);
}

void exposure_adj_set(exposure_state_t *state, int value)
{
    if (!state) { return; }

    /* Clamp adjustment at +/- 12 stops */
    if (value < -144 || value > 144) { return; }

    state->adjustment_value = value;
    exposure_recalculate(state);
}

int exposure_adj_min(exposure_state_t *state)
{
    // Adjustment to current base time that gets close to 0.01 seconds

    if (!state || state->base_time <= 0) { return 0; }

    float min_stops = logf(0.01f / state->base_time) / logf(2.0f);
    int min_adj = ceilf(min_stops * 12.0f);
    if (min_adj < -144) {
        min_adj = -144;
    }

    return min_adj;
}

int exposure_adj_max(exposure_state_t *state)
{
    // Adjustment to current base time that gets close to 999 seconds

    if (!state || state->base_time <= 0) { return 0; }

    float max_stops = logf(999.0f / state->base_time) / logf(2.0f);
    int max_adj = floorf(max_stops * 12.0f);
    if (max_adj > 144) {
        max_adj = 144;
    }

    return max_adj;
}

void exposure_contrast_increase(exposure_state_t *state)
{
    if (!state) { return; }

    if (state->contrast_grade < CONTRAST_GRADE_5) {
        state->contrast_grade++;
    }
}

void exposure_contrast_decrease(exposure_state_t *state)
{
    if (!state) { return; }

    if (state->contrast_grade > CONTRAST_GRADE_00) {
        state->contrast_grade--;
    }
}

void exposure_adj_increment_increase(exposure_state_t *state)
{
    if (!state) { return; }

    switch (state->adjustment_increment) {
    case EXPOSURE_ADJ_SIXTH:
        state->adjustment_increment = EXPOSURE_ADJ_TWELFTH;
        break;
    case EXPOSURE_ADJ_QUARTER:
        state->adjustment_increment = EXPOSURE_ADJ_SIXTH;
        break;
    case EXPOSURE_ADJ_THIRD:
        state->adjustment_increment = EXPOSURE_ADJ_QUARTER;
        break;
    case EXPOSURE_ADJ_HALF:
        state->adjustment_increment = EXPOSURE_ADJ_THIRD;
        break;
    case EXPOSURE_ADJ_WHOLE:
        state->adjustment_increment = EXPOSURE_ADJ_HALF;
        break;
    default:
        break;
    }
}

void exposure_adj_increment_decrease(exposure_state_t *state)
{
    if (!state) { return; }

    switch (state->adjustment_increment) {
    case EXPOSURE_ADJ_TWELFTH:
        state->adjustment_increment = EXPOSURE_ADJ_SIXTH;
        break;
    case EXPOSURE_ADJ_SIXTH:
        state->adjustment_increment = EXPOSURE_ADJ_QUARTER;
        break;
    case EXPOSURE_ADJ_QUARTER:
        state->adjustment_increment = EXPOSURE_ADJ_THIRD;
        break;
    case EXPOSURE_ADJ_THIRD:
        state->adjustment_increment = EXPOSURE_ADJ_HALF;
        break;
    case EXPOSURE_ADJ_HALF:
        state->adjustment_increment = EXPOSURE_ADJ_WHOLE;
        break;
    default:
        break;
    }
}

uint8_t exposure_adj_increment_get_denominator(const exposure_state_t *state)
{
    if (!state) { return 0; }

    switch (state->adjustment_increment) {
    case EXPOSURE_ADJ_TWELFTH:
        return 12;
    case EXPOSURE_ADJ_SIXTH:
        return 6;
    case EXPOSURE_ADJ_QUARTER:
        return 4;
    case EXPOSURE_ADJ_THIRD:
        return 3;
    case EXPOSURE_ADJ_HALF:
        return 2;
    case EXPOSURE_ADJ_WHOLE:
        return 1;
    default:
        return 0;
    }
}

float exposure_get_test_strip_time_incremental(const exposure_state_t *state,
    int patch_min, unsigned int patches_covered)
{
    if (!state) { return NAN; }

    if (patches_covered == 0) {
        float base_exposure = exposure_get_test_strip_time_complete(state, patch_min);
        return base_exposure;
    } else {
        float prev_exposure = exposure_get_test_strip_time_complete(state, patch_min + (patches_covered - 1));
        float curr_exposure = exposure_get_test_strip_time_complete(state, patch_min + patches_covered);
        return curr_exposure - prev_exposure;
    }
}

float exposure_get_test_strip_time_complete(const exposure_state_t *state, int patch)
{
    if (!state) { return NAN; }

    int patch_adjustment = state->adjustment_increment * patch;
    float patch_stops = patch_adjustment / 12.0f;
    float patch_time = state->adjusted_time * powf(2.0f, patch_stops);
    return patch_time;
}

void exposure_recalculate(exposure_state_t *state)
{
    float stops = state->adjustment_value / 12.0f;
    state->adjusted_time = state->base_time * powf(2.0f, stops);
}

const char *contrast_grade_str(exposure_contrast_grade_t contrast_grade)
{
    switch (contrast_grade) {
    case CONTRAST_GRADE_00:
        return "00";
    case CONTRAST_GRADE_0:
        return "0";
    case CONTRAST_GRADE_0_HALF:
        return "1/2";
    case CONTRAST_GRADE_1:
        return "1";
    case CONTRAST_GRADE_1_HALF:
        return "1-1/2";
    case CONTRAST_GRADE_2:
        return "2";
    case CONTRAST_GRADE_2_HALF:
        return "2-1/2";
    case CONTRAST_GRADE_3:
        return "3";
    case CONTRAST_GRADE_3_HALF:
        return "3-1/2";
    case CONTRAST_GRADE_4:
        return "4";
    case CONTRAST_GRADE_4_HALF:
        return "4-1/2";
    case CONTRAST_GRADE_5:
        return "5";
    default:
        return "";
    }
}
