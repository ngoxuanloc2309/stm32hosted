/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides network interface API
 */

#ifndef ESP_NETIF_H
#define ESP_NETIF_H

#include "esp_err.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct esp_netif {} esp_netif_t;

/* Network interface types */
typedef enum {
    ESP_NETIF_WIFI_STA = 0,
    ESP_NETIF_WIFI_AP,
    ESP_NETIF_ETH,
    ESP_NETIF_PPP,
    ESP_NETIF_SLIP,
    ESP_NETIF_LOWPAN6,
    ESP_NETIF_BT,
    ESP_NETIF_NAN,
} esp_netif_type_t;

/* IP info structure */
typedef struct {
    uint32_t ip;
    uint32_t netmask;
    uint32_t gw;
} esp_netif_ip_info_t;

/**
 * Initialize network interface
 */
esp_err_t esp_netif_init(void);

/**
 * Create network interface
 */
esp_netif_t* esp_netif_create_default_wifi_sta(void);

/**
 * Create AP network interface
 */
esp_netif_t* esp_netif_create_default_wifi_ap(void);

/**
 * Destroy network interface
 */
esp_err_t esp_netif_destroy(esp_netif_t* esp_netif);

/**
 * Set IP info
 */
esp_err_t esp_netif_set_ip_info(esp_netif_t* esp_netif, const esp_netif_ip_info_t* ip_info);

/**
 * Get IP info
 */
esp_err_t esp_netif_get_ip_info(esp_netif_t* esp_netif, esp_netif_ip_info_t* ip_info);

/**
 * Set MAC address
 */
esp_err_t esp_netif_set_mac(esp_netif_t* esp_netif, uint8_t mac[6]);

/**
 * Get MAC address
 */
esp_err_t esp_netif_get_mac(esp_netif_t* esp_netif, uint8_t mac[6]);

/**
 * Set default network interface
 */
esp_err_t esp_netif_set_default_netif(esp_netif_t* esp_netif);

/**
 * Get default network interface
 */
esp_netif_t* esp_netif_get_default_netif(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_NETIF_H */
