#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "paper_profile.h"

static void convert_exposure_float_to_display_timer(display_exposure_timer_t *elements, float exposure_time);

void convert_exposure_to_display_printing(display_main_printing_elements_t *elements, const exposure_state_t *exposure)
{
    elements->tone_graph = exposure_get_tone_graph(exposure);

    int paper_index = exposure_get_active_paper_profile_index(exposure);
    if (paper_index >= 0) {
        elements->paper_profile_num = paper_index + 1;
    } else {
        elements->paper_profile_num = 0;
    }

    elements->burn_dodge_count = exposure_burn_dodge_count(exposure);

    elements->contrast_grade = exposure_get_contrast_grade(exposure);

    elements->contrast_note = contrast_filter_str(
        exposure_get_contrast_filter(exposure),
        exposure_get_contrast_grade(exposure));

    float exposure_time = exposure_get_exposure_time(exposure);
    convert_exposure_float_to_display_timer(&(elements->time_elements), exposure_time);

    float min_exposure_time = exposure_get_min_exposure_time(exposure);
    elements->time_too_short = (min_exposure_time > 0) && (exposure_time < min_exposure_time);
}

void convert_exposure_to_display_densitometer(display_main_densitometer_elements_t *elements, const exposure_state_t *exposure)
{
    float density = exposure_get_relative_density(exposure);
    if (isnanf(density)) {
        elements->density_whole = UINT16_MAX;
        elements->density_fractional = UINT16_MAX;
        elements->fraction_digits = UINT8_MAX;
    } else {
        float whole;
        float fractional;
        fractional = modff(density, &whole);
        elements->density_whole = whole;
        elements->density_fractional = round_to_10(roundf(fractional * 1000.0f));
        elements->fraction_digits = 2;
    }
}

void convert_exposure_to_display_calibration(display_main_calibration_elements_t *elements, const exposure_state_t *exposure)
{
    elements->cal_title1 = "Print";
    elements->cal_title2 = "Exposure";
    elements->cal_value = exposure_get_calibration_pev(exposure);

    float exposure_time = exposure_get_exposure_time(exposure);
    convert_exposure_float_to_display_timer(&(elements->time_elements), exposure_time);

    float min_exposure_time = exposure_get_min_exposure_time(exposure);
    elements->time_too_short = (min_exposure_time > 0) && (exposure_time < min_exposure_time);
}

void convert_exposure_float_to_display_timer(display_exposure_timer_t *elements, float exposure_time)
{
    float seconds;
    float fractional;
    fractional = modff(exposure_time, &seconds);
    elements->time_seconds = seconds;
    elements->time_milliseconds = round_to_10(roundf(fractional * 1000.0f));

    if (exposure_time < 10) {
        elements->fraction_digits = 2;

    } else if (exposure_time < 100) {
        elements->fraction_digits = 1;
    } else {
        elements->fraction_digits = 0;
    }
}

void convert_exposure_to_display_timer(display_exposure_timer_t *elements, uint32_t exposure_ms)
{
    update_display_timer(elements, exposure_ms);

    if (exposure_ms < 10000) {
        elements->fraction_digits = 2;

    } else if (exposure_ms < 100000) {
        elements->fraction_digits = 1;
    } else {
        elements->fraction_digits = 0;
    }
}

void update_display_timer(display_exposure_timer_t *elements, uint32_t exposure_ms)
{
    elements->time_seconds = exposure_ms / 1000;
    elements->time_milliseconds = round_to_10(exposure_ms % 1000);
}

uint32_t round_to_10(uint32_t n)
{
    uint32_t a = (n / 10) * 10;
    uint32_t b = a + 10;
    return (n - a > b - n) ? b : a;
}

uint32_t rounded_exposure_time_ms(float seconds)
{
    uint32_t milliseconds = (uint32_t)(roundf(seconds * 1000.0f));
    if (milliseconds > 1000000) {
        milliseconds = 1000000;
    }
    milliseconds = round_to_10(milliseconds);
    return milliseconds;
}

size_t pad_str_to_length(char *str, char c, size_t length)
{
    if (!str) {
        return 0;
    }

    size_t i = strlen(str);
    if (i >= length) {
        return i;
    }

    while (i <= length) {
        str[i++] = c;
    }
    str[i] = '\0';

    return i - 1;
}

size_t append_signed_fraction(char *str, int8_t numerator, uint8_t denominator)
{
    size_t count = 0;
    bool num_positive = numerator >= 0;
    char val_sign = num_positive ? '+' : '-';
    uint8_t val_num = abs(numerator);
    uint8_t val_whole = val_num / denominator;
    val_num -= val_whole * denominator;

    if (!str) {
        return count;
    }

    if (val_whole != 0 || (val_whole == 0 && val_num == 0)) {
        if (val_num > 0) {
            // Whole with fraction
            count = sprintf(str, "%c%d-%d/%d",
                val_sign, val_whole, val_num, denominator);
        } else {
            // Whole without fraction
            count = sprintf(str, "%c%d",
                val_sign, val_whole);
        }
    } else {
        // Just the fraction
        count = sprintf(str, "%c%d/%d",
            val_sign, val_num, denominator);
    }
    return count;
}

size_t append_exposure_time(char *str, float time)
{
    size_t count = 0;
    uint32_t exposure_ms = rounded_exposure_time_ms(time);
    uint16_t display_seconds = exposure_ms / 1000;
    uint16_t display_milliseconds = round_to_10(exposure_ms % 1000);

    if (exposure_ms < 10000) {
        count = sprintf(str, "%01d.%02ds", display_seconds, display_milliseconds / 10);
    } else if (exposure_ms < 100000) {
        count = sprintf(str, "%d.%01ds", display_seconds, display_milliseconds / 100);
    } else {
        count = sprintf(str, "%ds", display_seconds);
    }
    return count;
}

float interpolate(float x1, float y1, float x2, float y2, float x3, float y3, float x)
{
    return (y1 * ((x - x2) / (x1 - x2)) * ((x - x3) / (x1 - x3))) +
        (y2 * ((x - x1) / (x2 - x1)) * ((x - x3) / (x2 - x3))) +
        (y3 * ((x - x1) / (x3 - x1)) * ((x - x2) / (x3 - x2)));
}

bool is_valid_number(float num)
{
    return isnormal(num) || fpclassify(num) == FP_ZERO;
}
