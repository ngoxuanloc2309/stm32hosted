/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi HE (802.11ax) API
 */

#ifndef ESP_WIFI_HE_H
#define ESP_WIFI_HE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize WiFi HE
 */
esp_err_t esp_wifi_he_init(void);

/**
 * Deinit WiFi HE
 */
esp_err_t esp_wifi_he_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_WIFI_HE_H */
