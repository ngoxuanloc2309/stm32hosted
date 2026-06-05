/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi default API
 */

#ifndef ESP_WIFI_DEFAULT_H
#define ESP_WIFI_DEFAULT_H

#include "esp_netif.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create default WiFi STA interface
 */
esp_netif_t *esp_wifi_set_default_wifi_sta_handlers(void);

/**
 * Create default WiFi AP interface
 */
esp_netif_t *esp_wifi_set_default_wifi_ap_handlers(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_WIFI_DEFAULT_H */
