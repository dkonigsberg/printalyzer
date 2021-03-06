#include "main_menu.h"

#include <FreeRTOS.h>
#include <task.h>
#include <esp_log.h>

#include <stdio.h>
#include <string.h>

#include "display.h"
#include "keypad.h"
#include "led.h"
#include "util.h"
#include "app_descriptor.h"

#include "menu_settings.h"
#include "menu_enlarger.h"
#include "menu_paper.h"
#include "menu_step_wedge.h"
#include "menu_import_export.h"
#include "menu_diagnostics.h"

static const char *TAG = "main_menu";

static menu_result_t menu_about();

menu_result_t main_menu_start(state_controller_t *controller)
{
    ESP_LOGI(TAG, "Main menu");

    menu_result_t menu_result = MENU_OK;
    uint8_t option = 1;

    do {
        option = display_selection_list(
                "Main Menu", option,
                "Settings\n"
                "Enlarger Profiles\n"
                "Paper Profiles\n"
                "Step Wedge Properties\n"
                "Import / Export\n"
                "Diagnostics\n"
                "About");

        if (option == 1) {
            menu_result = menu_settings();
        } else if (option == 2) {
            menu_result = menu_enlarger_profiles(controller);
        } else if (option == 3) {
            menu_result = menu_paper_profiles(controller);
        } else if (option == 4) {
            menu_result = menu_step_wedge();
        } else if (option == 5) {
            menu_result = menu_import_export(controller);
        } else if (option == 6) {
            menu_result = menu_diagnostics();
        } else if (option == 7) {
            menu_result = menu_about();
        } else if (option == UINT8_MAX) {
            menu_result = MENU_TIMEOUT;
        }
    } while (option > 0 && menu_result != MENU_TIMEOUT);

    return menu_result;
}

menu_result_t menu_confirm_cancel(const char *title)
{
    uint8_t option;
    char buf[128];

    if (title && strlen(title) > 0) {
        sprintf(buf, "%s\n", title);
    } else {
        sprintf(buf, "\n");
    }

    option = display_message(buf, "Would you like to save changes?", "\n",
        " Yes \n No \n Cancel ");

    if (option == 1) {
        return MENU_SAVE;
    } else if (option == 2) {
        return MENU_OK;
    } else if (option == UINT8_MAX) {
        return MENU_TIMEOUT;
    } else {
        return MENU_CANCEL;
    }
}

size_t menu_build_padded_str_row(char *buf, const char *label, const char *value)
{
    size_t offset = 0;
    size_t label_len = strlen(label);
    size_t value_len = MIN(strlen(value), DISPLAY_MENU_ROW_LENGTH - (label_len + 2));

    strcpy(buf, label);
    strcat(buf, " ");

    offset = pad_str_to_length(buf, ' ', DISPLAY_MENU_ROW_LENGTH - (value_len + 2));
    buf[offset++] = '[';
    strncpy(buf + offset, value, value_len + 1);
    offset += value_len;
    buf[offset++] = ']';
    buf[offset++] = '\n';
    buf[offset] = '\0';
    return offset;
}

menu_result_t menu_about()
{
    const app_descriptor_t *app_descriptor = app_descriptor_get();
    menu_result_t menu_result = MENU_OK;
    char buf[384];

    sprintf(buf,
        "Enlarging Timer & Exposure Meter\n"
        "\n"
        "%s (%s)\n"
        "%s\n",
        app_descriptor->version,
        app_descriptor->build_describe,
        app_descriptor->build_date);

    uint8_t option = display_message(
        app_descriptor->project_name,
        NULL,
        buf, " OK ");
    if (option == UINT8_MAX) {
        menu_result = MENU_TIMEOUT;
    }
    return menu_result;
}
