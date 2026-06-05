/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi API
 */

#ifndef ESP_WIFI_H
#define ESP_WIFI_H

#include "esp_err.h"
#include "esp_wifi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize WiFi
 */
esp_err_t esp_wifi_init(const void* config);

/**
 * Deinit WiFi
 */
esp_err_t esp_wifi_deinit(void);

/**
 * Set WiFi mode
 */
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);

/**
 * Get WiFi mode
 */
esp_err_t esp_wifi_get_mode(wifi_mode_t* mode);

/**
 * Start WiFi
 */
esp_err_t esp_wifi_start(void);

/**
 * Stop WiFi
 */
esp_err_t esp_wifi_stop(void);

/**
 * Set WiFi config for STA
 */
esp_err_t esp_wifi_set_config(uint32_t interface, wifi_config_t* conf);

/**
 * Get WiFi config
 */
esp_err_t esp_wifi_get_config(uint32_t interface, wifi_config_t* conf);

/**
 * Connect to AP
 */
esp_err_t esp_wifi_connect(void);

/**
 * Disconnect from AP
 */
esp_err_t esp_wifi_disconnect(void);

/**
 * Start WiFi scan
 */
esp_err_t esp_wifi_scan_start(const void* config, uint8_t block);

/**
 * Scan result
 */
typedef struct {
    uint8_t bssid[6];
    uint8_t ssid[32];
    uint8_t ssid_len;
    uint8_t channel;
    int8_t rssi;
    wifi_auth_mode_t authmode;
} wifi_ap_record_t;

/**
 * Get WiFi scan results
 */
esp_err_t esp_wifi_scan_get_ap_records(uint16_t *number, wifi_ap_record_t *ap_records);

/**
 * Enable power save mode
 */
esp_err_t esp_wifi_set_ps(uint8_t type);

/**
 * Get WiFi power save mode
 */
esp_err_t esp_wifi_get_ps(uint8_t* type);

#ifdef __cplusplus
}
#endif

#endif /* ESP_WIFI_H */
