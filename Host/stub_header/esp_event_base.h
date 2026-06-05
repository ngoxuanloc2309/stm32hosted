/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides event base definitions
 */

#ifndef ESP_EVENT_BASE_H
#define ESP_EVENT_BASE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Define event base IDs */
#define WIFI_EVENT      ((const char*)"wifi_event")
#define IP_EVENT        ((const char*)"ip_event")
#define BT_DEVICE_EVENT ((const char*)"bt_device_event")

/* WiFi events */
typedef enum {
    WIFI_EVENT_WIFI_READY = 0,
    WIFI_EVENT_SCAN_DONE,
    WIFI_EVENT_STA_START,
    WIFI_EVENT_STA_STOP,
    WIFI_EVENT_STA_CONNECTED,
    WIFI_EVENT_STA_DISCONNECTED,
    WIFI_EVENT_STA_AUTHMODE_CHANGE,
    WIFI_EVENT_STA_WPS_ER_SUCCESS,
    WIFI_EVENT_STA_WPS_ER_FAILED,
    WIFI_EVENT_STA_WPS_ER_TIMEOUT,
    WIFI_EVENT_STA_WPS_ER_PIN,
    WIFI_EVENT_AP_START,
    WIFI_EVENT_AP_STOP,
    WIFI_EVENT_AP_STACONNECTED,
    WIFI_EVENT_AP_STADISCONNECTED,
    WIFI_EVENT_AP_PROBEREQRECVED,
    WIFI_EVENT_FTM_REPORT,
    WIFI_EVENT_STA_BSS_RSSI_LOW,
    WIFI_EVENT_ACTION_TX_STATUS,
    WIFI_EVENT_ROC_DONE,
    WIFI_EVENT_STA_BEACON_TIMEOUT,
} wifi_event_t;

/* IP events */
typedef enum {
    IP_EVENT_STA_GOT_IP = 0,
    IP_EVENT_STA_LOST_IP,
    IP_EVENT_AP_STAIPASSIGNED,
    IP_EVENT_GOT_IP6,
    IP_EVENT_ETH_GOT_IP,
    IP_EVENT_ETH_LOST_IP,
    IP_EVENT_PPP_GOT_IP,
    IP_EVENT_PPP_LOST_IP,
} ip_event_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP_EVENT_BASE_H */
