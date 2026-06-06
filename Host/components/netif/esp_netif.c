#include "lwip/pbuf.h"
#include "lwip/netif.h"
#include "lwip/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/tcpip.h"
#include "netdev_api.h"
#include "esp_netif.h"
#include "common.h"
#include <string.h>

#define IFNAME0                 'e'
#define IFNAME1                 's'
#define ESP_NETIF_MTU           1500
#define ESP_NETIF_HOSTNAME      "synaptix"

static struct netif          sta_netif;
static struct network_handle *sta_net_handle = NULL;
static uint8_t               sta_mac[6]      = {0x02, 0x00, 0x00, 0x00, 0x00, 0x01};

/* ==== TX path: lwIP -> esp_hosted ==== */
static err_t low_level_output(struct netif *netif, struct esp_pbuf *p)
{
    struct esp_pbuf *q;
    struct esp_pbuf esp_buf;
    uint8_t *tx_data;
    uint16_t total_len = p->tot_len;

    tx_data = (uint8_t *)pvPortMalloc(total_len);
    if (!tx_data)
        return ERR_MEM;

    uint16_t offset = 0;
    for (q = p; q != NULL; q = q->next) {
        memcpy(tx_data + offset, q->payload, q->len);
        offset += q->len;
    }

    esp_buf.payload = tx_data;
    esp_buf.len     = total_len;

    int ret = network_write(sta_net_handle, &esp_buf);

    vPortFree(tx_data);
    return (ret == 0) ? ERR_OK : ERR_IF;
}

/* ==== RX path: esp_hosted -> lwIP ==== */
static void sta_rx_callback(struct network_handle *net_handle)
{
    struct pbuf *esp_buf = network_read(net_handle, 0);
    if (!esp_buf)
        return;

    struct pbuf *p = pbuf_alloc(PBUF_RAW, esp_buf->len, PBUF_POOL);
    if (!p) {
        vPortFree(esp_buf->payload);
        vPortFree(esp_buf);
        return;
    }

    memcpy(p->payload, esp_buf->payload, esp_buf->len);

    vPortFree(esp_buf->payload);
    vPortFree(esp_buf);

    if (sta_netif.input(p, &sta_netif) != ERR_OK)
        pbuf_free(p);
}

/* ==== lwIP netif init callback ==== */
static err_t esp_netif_init_cb(struct netif *netif)
{
    netif->hwaddr_len = ETHARP_HWADDR_LEN;
    memcpy(netif->hwaddr, sta_mac, ETHARP_HWADDR_LEN);
    netif->mtu        = ESP_NETIF_MTU;
    netif->flags      = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

#if LWIP_NETIF_HOSTNAME
    netif->hostname   = ESP_NETIF_HOSTNAME;
#endif

    netif->name[0]    = IFNAME0;
    netif->name[1]    = IFNAME1;
    netif->output     = etharp_output;
    netif->linkoutput = low_level_output;

    return ERR_OK;
}

/* ==== Public API ==== */
int esp_netif_init(void)
{
    // lwip_init();

    ip4_addr_t ipaddr, netmask, gw;
    IP4_ADDR(&ipaddr,  0, 0, 0, 0);
    IP4_ADDR(&netmask, 0, 0, 0, 0);
    IP4_ADDR(&gw,      0, 0, 0, 0);

    if (!netif_add(&sta_netif, &ipaddr, &netmask, &gw,
                   NULL, esp_netif_init_cb, tcpip_input)) {
        printf("esp_netif_init: netif_add failed\r\n");
        return -1;
    }

    netif_set_default(&sta_netif);

    sta_net_handle = network_open(STA_INTERFACE, sta_rx_callback);
    if (!sta_net_handle) {
        printf("esp_netif_init: network_open failed\r\n");
        return -1;
    }

    return 0;
}

void esp_netif_deinit(void)
{
    dhcp_stop(&sta_netif);
    netif_remove(&sta_netif);
    if (sta_net_handle) {
        network_close(sta_net_handle);
        sta_net_handle = NULL;
    }
}

struct netif *esp_netif_get_sta(void)
{
    return &sta_netif;
}

void esp_netif_sta_up(void)
{
    netif_set_link_up(&sta_netif);
    netif_set_up(&sta_netif);
    dhcp_start(&sta_netif);
}

void esp_netif_sta_down(void)
{
    dhcp_stop(&sta_netif);
    netif_set_link_down(&sta_netif);
    netif_set_down(&sta_netif);
}

int esp_netif_is_sta_connected(void)
{
    return !ip4_addr_isany_val(*netif_ip4_addr(&sta_netif));
}