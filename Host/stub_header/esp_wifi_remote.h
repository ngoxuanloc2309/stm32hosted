/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi remote control API
 */

#ifndef ESP_WIFI_REMOTE_H
#define ESP_WIFI_REMOTE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize WiFi remote
 */
esp_err_t esp_wifi_remote_init(void);

/**
 * Deinit WiFi remote
 */
esp_err_t esp_wifi_remote_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_WIFI_REMOTE_H */
