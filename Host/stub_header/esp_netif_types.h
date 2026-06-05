/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides network type definitions
 */

#ifndef ESP_NETIF_TYPES_H
#define ESP_NETIF_TYPES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Network interface event IDs */
typedef enum {
    NETIF_IP_EVENT_GOT_IP,
    NETIF_IP_EVENT_LOST_IP,
    NETIF_IP_EVENT_GOT_IP6,
} netif_event_t;

/* DHCP states */
typedef enum {
    DHCP_STOPPED = 0,
    DHCP_STARTED = 1,
} dhcp_status_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP_NETIF_TYPES_H */
