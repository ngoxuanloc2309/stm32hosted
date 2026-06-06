#ifndef __ESP_NETIF_H
#define __ESP_NETIF_H

#include "lwip/netif.h"
#include "lwip/ip_addr.h"
// #include "netdev_api.h"
struct network_handle;

#ifdef __cplusplus
extern "C" {
#endif

/* ==== Exported Functions ==== */

/*
 * Initialize esp_hosted lwIP netif for STA interface.
 * Must be called after transport is active and network_open() succeeds.
 * Returns 0 on success, -1 on failure.
 */
int esp_netif_init(void);

/*
 * Deinitialize esp_hosted lwIP netif.
 */
void esp_netif_deinit(void);

/*
 * Get lwIP netif handle for STA interface.
 */
struct netif *esp_netif_get_sta(void);

/*
 * Called when WiFi station connects and IP is assigned.
 * Brings lwIP netif up.
 */
void esp_netif_sta_up(void);

/*
 * Called when WiFi station disconnects.
 * Brings lwIP netif down.
 */
void esp_netif_sta_down(void);

/*
 * Check if STA netif has valid IP.
 * Returns 1 if IP assigned, 0 otherwise.
 */
int esp_netif_is_sta_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* __ESP_NETIF_H */