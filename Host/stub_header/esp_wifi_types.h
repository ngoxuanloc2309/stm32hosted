/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi types
 */

#ifndef ESP_WIFI_TYPES_H
#define ESP_WIFI_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* WiFi modes */
typedef enum {
    WIFI_MODE_NULL = 0,
    WIFI_MODE_STA,
    WIFI_MODE_AP,
    WIFI_MODE_APSTA,
} wifi_mode_t;

/* WiFi authentication mode */
typedef enum {
    WIFI_AUTH_OPEN = 0,
    WIFI_AUTH_WEP,
    WIFI_AUTH_WPA_PSK,
    WIFI_AUTH_WPA2_PSK,
    WIFI_AUTH_WPA_WPA2_PSK,
    WIFI_AUTH_WPA2_ENTERPRISE,
    WIFI_AUTH_WPA3_PSK,
    WIFI_AUTH_WPA2_WPA3_PSK,
    WIFI_AUTH_WAPI_PSK,
    WIFI_AUTH_MAX,
} wifi_auth_mode_t;

/* Scan types */
typedef enum {
    WIFI_SCAN_TYPE_ACTIVE = 0,
    WIFI_SCAN_TYPE_PASSIVE,
} wifi_scan_type_t;

/* AP config structure */
typedef struct {
    uint8_t ssid[32];
    uint8_t ssid_len;
    uint8_t password[64];
    uint8_t channel;
    wifi_auth_mode_t authmode;
    uint8_t ssid_hidden;
    uint8_t max_connection;
    uint16_t beacon_interval;
} wifi_ap_config_t;

/* STA config structure */
typedef struct {
    uint8_t ssid[32];
    uint8_t password[64];
    uint8_t scan_method;
    uint8_t bssid_set;
    uint8_t bssid[6];
    uint8_t channel;
    uint8_t listen_interval;
    uint32_t sort_method;
} wifi_sta_config_t;

/* WiFi config structure */
typedef struct {
    wifi_ap_config_t ap;
    wifi_sta_config_t sta;
} wifi_config_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP_WIFI_TYPES_H */
