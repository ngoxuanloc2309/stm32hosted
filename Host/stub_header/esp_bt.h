/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides Bluetooth API
 */

#ifndef ESP_BT_H
#define ESP_BT_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize Bluetooth
 */
esp_err_t esp_bt_controller_init(void* cfg);

/**
 * Enable Bluetooth
 */
esp_err_t esp_bt_controller_enable(int mode);

/**
 * Disable Bluetooth
 */
esp_err_t esp_bt_controller_disable(void);

/**
 * Deinit Bluetooth controller
 */
esp_err_t esp_bt_controller_deinit(void);

/**
 * Get Bluetooth status
 */
int esp_bt_controller_get_status(void);

/* Bluetooth modes */
typedef enum {
    ESP_BT_MODE_IDLE = 0x0,
    ESP_BT_MODE_BLE = 0x1,
    ESP_BT_MODE_CLASSIC_BT = 0x2,
    ESP_BT_MODE_BTDM = 0x3,
} esp_bt_mode_t;

/**
 * Get BLE address
 */
esp_err_t esp_read_mac(uint8_t* mac, int type);

#ifdef __cplusplus
}
#endif

#endif /* ESP_BT_H */
