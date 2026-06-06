#ifndef __LWIPOPTS_H
#define __LWIPOPTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ==== System ==== */
#define NO_SYS                          0
#define LWIP_SOCKET                     1
#define LWIP_NETCONN                    1
#define SYS_LIGHTWEIGHT_PROT            1

/* ==== Memory ==== */
#define MEM_ALIGNMENT                   4
#define MEM_SIZE                        (16 * 1024)
#define MEMP_NUM_PBUF                   16
#define MEMP_NUM_TCP_PCB                8
#define MEMP_NUM_TCP_PCB_LISTEN         4
#define MEMP_NUM_TCP_SEG                32
#define MEMP_NUM_UDP_PCB                4
#define MEMP_NUM_NETBUF                 8
#define MEMP_NUM_NETCONN                8
#define MEMP_NUM_SYS_TIMEOUT            10

/* ==== Pbuf ==== */
#define PBUF_POOL_SIZE                  16
#define PBUF_POOL_BUFSIZE               1600

/* ==== TCP ==== */
#define LWIP_TCP                        1
#define TCP_TTL                         255
#define TCP_MSS                         1460
#define TCP_WND                         (4 * TCP_MSS)
#define TCP_SND_BUF                     (4 * TCP_MSS)
#define TCP_SND_QUEUELEN                (2 * TCP_SND_BUF / TCP_MSS)
#define LWIP_TCP_KEEPALIVE              1

/* ==== UDP ==== */
#define LWIP_UDP                        1
#define UDP_TTL                         255

/* ==== ICMP ==== */
#define LWIP_ICMP                       1

/* ==== DHCP ==== */
#define LWIP_DHCP                       1
#define LWIP_DHCP_MAX_NTP_SERVERS       0

/* ==== DNS ==== */
#define LWIP_DNS                        1
#define DNS_MAX_SERVERS                 2

/* ==== ARP ==== */
#define LWIP_ARP                        1
#define ARP_TABLE_SIZE                  4
#define ARP_QUEUEING                    1

/* ==== Netif ==== */
#define LWIP_NETIF_HOSTNAME             1
#define LWIP_NETIF_STATUS_CALLBACK      1
#define LWIP_NETIF_LINK_CALLBACK        1

/* ==== FreeRTOS Integration ==== */
#define LWIP_COMPAT_MUTEX               0
#define LWIP_COMPAT_MUTEX_ALLOWED       1

/* ==== Stats (disable to save memory) ==== */
#define LWIP_STATS                      0
#define LWIP_STATS_DISPLAY              0

/* ==== Checksum ==== */
#define CHECKSUM_BY_HARDWARE            0

/* ==== Debug (disable in production) ==== */
#define LWIP_DEBUG                      0

/* ==== Misc ==== */
#define LWIP_SO_RCVTIMEO                1
#define LWIP_SO_SNDTIMEO                1
#define LWIP_BROADCAST_PING             1

#ifdef __cplusplus
}
#endif

#endif /* __LWIPOPTS_H */