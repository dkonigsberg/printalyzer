#ifndef DISPLAY_ASSETS_H
#define DISPLAY_ASSETS_H

#include <stdint.h>

typedef struct {
    uint8_t *bits;
    uint16_t width;
    uint16_t height;
} asset_info_t;

typedef enum {
    ASSET_PRINTALYZER = 0,
    ASSET_TIMER_ICON_48,
    ASSET_TIMER_ICON_24,
    ASSET_EXPOSURE_ADJ_ICON_48,
    ASSET_TIMER_ADJ_ICON_48,
    ASSET_PHOTO_ICON_24,
    ASSET_ADJUST_ICON_24,
    ASSET_ADJUST_COUNT_1_18,
    ASSET_ADJUST_COUNT_2_18,
    ASSET_ADJUST_COUNT_3_18,
    ASSET_ADJUST_COUNT_4_18,
    ASSET_ADJUST_COUNT_5_18,
    ASSET_ADJUST_COUNT_6_18,
    ASSET_ADJUST_COUNT_7_18,
    ASSET_ADJUST_COUNT_8_18,
    ASSET_ADJUST_COUNT_9_18,
    ASSET_ADJUST_COUNT_9P_18,
    ASSET_ARROW_UP_18,
    ASSET_ARROW_DOWN_18,
    ASSET_MAX
} asset_name_t;

uint8_t display_asset_get(asset_info_t *asset_info, asset_name_t asset_name);

#endif /* DISPLAY_ASSETS_H */
