#include "relay.h"

#include <string.h>
#include <esp_log.h>

static relay_handle_t relay_handle = {0};

static const char *TAG = "relay";

HAL_StatusTypeDef relay_init(const relay_handle_t *handle)
{
    ESP_LOGD(TAG, "relay_init");

    if (!handle) {
        ESP_LOGE(TAG, "Relay handle not initialized");
        return HAL_ERROR;
    }

    memcpy(&relay_handle, handle, sizeof(relay_handle_t));

    /* Start with both relays in a known disengaged state */
    HAL_GPIO_WritePin(relay_handle.enlarger_gpio_port, relay_handle.enlarger_gpio_pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(relay_handle.safelight_gpio_port, relay_handle.safelight_gpio_pin, GPIO_PIN_RESET);

    return HAL_OK;
}

void relay_enlarger_enable(bool enabled)
{
    HAL_GPIO_WritePin(relay_handle.enlarger_gpio_port, relay_handle.enlarger_gpio_pin,
        enabled ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void relay_safelight_enable(bool enabled)
{
    HAL_GPIO_WritePin(relay_handle.safelight_gpio_port, relay_handle.safelight_gpio_pin,
        enabled ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
