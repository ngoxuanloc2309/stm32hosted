/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides MAC address operations
 */

#ifndef ESP_MAC_H
#define ESP_MAC_H

#include "esp_err.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* MAC types */
typedef enum {
    ESP_MAC_WIFI_STA,
    ESP_MAC_WIFI_AP,
    ESP_MAC_BT,
    ESP_MAC_BLE,
    ESP_MAC_ETH,
    ESP_MAC_IEEE802154,
} esp_mac_type_t;

/**
 * Set MAC address
 */
esp_err_t esp_base_mac_addr_set(const uint8_t *mac);

/**
 * Get MAC address
 */
esp_err_t esp_read_mac(uint8_t* mac, esp_mac_type_t type);

/**
 * Get base MAC address
 */
esp_err_t esp_efuse_read_mac(uint8_t* mac);

/**
 * Get random MAC address (used for STA mode)
 */
esp_err_t esp_get_random_mac(uint8_t* mac);

#ifdef __cplusplus
}
#endif

#endif /* ESP_MAC_H */
