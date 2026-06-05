# =============================================================================
# Host Directory Base
# =============================================================================
HOST_DIR            = Host

# =============================================================================
# esp-hosted-mcu
# =============================================================================
ESP_HOSTED_DIR      = $(HOST_DIR)/lib/esp-hosted-mcu
ESP_HOSTED_HOST     = $(ESP_HOSTED_DIR)/host
ESP_HOSTED_COMMON   = $(ESP_HOSTED_DIR)/common

# =============================================================================
# lwIP
# =============================================================================
LWIP_DIR            = $(HOST_DIR)/lib/lwip
LWIP_SRC            = $(LWIP_DIR)/src

# =============================================================================
# App
# =============================================================================
APP_FILES = \
    $(HOST_DIR)/app/app_main.c

# =============================================================================
# Port layer (STM32H5 HAL wrappers - tự viết)
# =============================================================================
PORT_FILES = \
    $(HOST_DIR)/port/port_spi.c       \
    $(HOST_DIR)/port/port_os.c        \
    $(HOST_DIR)/port/port_gpio.c      \
    $(HOST_DIR)/port/port_netif.c

# =============================================================================
# Services
# =============================================================================
SERVICES_FILES = \
    $(HOST_DIR)/services/wifi_service/wifi_service.c    \
    $(HOST_DIR)/services/mqtt_service/mqtt_service.c

# =============================================================================
# esp-hosted-mcu: API
# =============================================================================
ESP_HOSTED_API_FILES = \
    $(ESP_HOSTED_HOST)/api/src/esp_hosted_api.c             \
    $(ESP_HOSTED_HOST)/api/src/esp_hosted_transport_config.c

# =============================================================================
# esp-hosted-mcu: Drivers - Transport SPI only
# =============================================================================
ESP_HOSTED_TRANSPORT_FILES = \
    $(ESP_HOSTED_HOST)/drivers/transport/transport_drv.c    \
    $(ESP_HOSTED_HOST)/drivers/transport/transport_util.c   \
    $(ESP_HOSTED_HOST)/drivers/transport/spi/spi_drv.c

# =============================================================================
# esp-hosted-mcu: Drivers - RPC
# =============================================================================
ESP_HOSTED_RPC_FILES = \
    $(ESP_HOSTED_HOST)/drivers/rpc/core/rpc_core.c      \
    $(ESP_HOSTED_HOST)/drivers/rpc/core/rpc_evt.c       \
    $(ESP_HOSTED_HOST)/drivers/rpc/core/rpc_req.c       \
    $(ESP_HOSTED_HOST)/drivers/rpc/core/rpc_rsp.c       \
    $(ESP_HOSTED_HOST)/drivers/rpc/core/rpc_utils.c     \
    $(ESP_HOSTED_HOST)/drivers/rpc/slaveif/rpc_slave_if.c \
    $(ESP_HOSTED_HOST)/drivers/rpc/wrap/rpc_wrap.c

# =============================================================================
# esp-hosted-mcu: Drivers - Serial
# =============================================================================
ESP_HOSTED_SERIAL_FILES = \
    $(ESP_HOSTED_HOST)/drivers/serial/serial_drv.c      \
    $(ESP_HOSTED_HOST)/drivers/serial/serial_ll_if.c    \
    $(ESP_HOSTED_HOST)/drivers/virtual_serial_if/src/serial_if.c

# =============================================================================
# esp-hosted-mcu: Common - protobuf + mempool + utils
# =============================================================================
ESP_HOSTED_COMMON_FILES = \
    $(ESP_HOSTED_COMMON)/proto/esp_hosted_rpc.pb-c.c    \
    $(ESP_HOSTED_COMMON)/mempool/mempool.c              \
    $(ESP_HOSTED_COMMON)/mempool/mempool_ll.c           \
    $(ESP_HOSTED_COMMON)/utils/esp_hosted_cli.c         \
    $(ESP_HOSTED_COMMON)/protobuf-c/protobuf-c/protobuf-c.c

# =============================================================================
# lwIP core
# =============================================================================
LWIP_CORE_FILES = \
    $(LWIP_SRC)/core/init.c             \
    $(LWIP_SRC)/core/def.c              \
    $(LWIP_SRC)/core/dns.c              \
    $(LWIP_SRC)/core/inet_chksum.c      \
    $(LWIP_SRC)/core/ip.c               \
    $(LWIP_SRC)/core/mem.c              \
    $(LWIP_SRC)/core/memp.c             \
    $(LWIP_SRC)/core/netif.c            \
    $(LWIP_SRC)/core/pbuf.c             \
    $(LWIP_SRC)/core/raw.c              \
    $(LWIP_SRC)/core/stats.c            \
    $(LWIP_SRC)/core/sys.c              \
    $(LWIP_SRC)/core/altcp.c            \
    $(LWIP_SRC)/core/altcp_alloc.c      \
    $(LWIP_SRC)/core/altcp_tcp.c        \
    $(LWIP_SRC)/core/tcp.c              \
    $(LWIP_SRC)/core/tcp_in.c           \
    $(LWIP_SRC)/core/tcp_out.c          \
    $(LWIP_SRC)/core/timeouts.c         \
    $(LWIP_SRC)/core/udp.c              \
    $(LWIP_SRC)/core/ipv4/icmp.c        \
    $(LWIP_SRC)/core/ipv4/igmp.c        \
    $(LWIP_SRC)/core/ipv4/ip4.c         \
    $(LWIP_SRC)/core/ipv4/ip4_addr.c    \
    $(LWIP_SRC)/core/ipv4/ip4_frag.c    \
    $(LWIP_SRC)/core/ipv4/autoip.c      \
    $(LWIP_SRC)/core/ipv4/dhcp.c        \
    $(LWIP_SRC)/core/ipv4/etharp.c      \
    $(LWIP_SRC)/netif/ethernet.c        \
    $(LWIP_SRC)/api/api_lib.c           \
    $(LWIP_SRC)/api/api_msg.c           \
    $(LWIP_SRC)/api/err.c               \
    $(LWIP_SRC)/api/if_api.c            \
    $(LWIP_SRC)/api/netbuf.c            \
    $(LWIP_SRC)/api/netdb.c             \
    $(LWIP_SRC)/api/netifapi.c          \
    $(LWIP_SRC)/api/sockets.c           \
    $(LWIP_SRC)/api/tcpip.c             \
    $(LWIP_SRC)/apps/mqtt/mqtt.c

# =============================================================================
# lwIP sys_arch (FreeRTOS port by ST)
# =============================================================================
LWIP_SYS_FILES = \
    $(LWIP_DIR)/system/OS/sys_arch.c

# =============================================================================
# All Host Sources
# =============================================================================
HOST_SOURCES = \
    $(APP_FILES)                    \
    $(PORT_FILES)                   \
    $(SERVICES_FILES)               \
    $(ESP_HOSTED_API_FILES)         \
    $(ESP_HOSTED_TRANSPORT_FILES)   \
    $(ESP_HOSTED_RPC_FILES)         \
    $(ESP_HOSTED_SERIAL_FILES)      \
    $(ESP_HOSTED_COMMON_FILES)      \
    $(LWIP_CORE_FILES)              \
    $(LWIP_SYS_FILES)

# =============================================================================
# Include Paths
# =============================================================================
HOST_INCLUDES = \
    -I$(HOST_DIR)/app                                           \
    -I$(HOST_DIR)/port                                          \
    -I$(HOST_DIR)/services/wifi_service                         \
    -I$(HOST_DIR)/services/mqtt_service                         \
    -I$(ESP_HOSTED_HOST)                                        \
    -I$(ESP_HOSTED_HOST)/api/include                            \
    -I$(ESP_HOSTED_HOST)/api/priv                               \
    -I$(ESP_HOSTED_HOST)/drivers/transport                      \
    -I$(ESP_HOSTED_HOST)/drivers/transport/spi                  \
    -I$(ESP_HOSTED_HOST)/drivers/rpc/core                       \
    -I$(ESP_HOSTED_HOST)/drivers/rpc/slaveif                    \
    -I$(ESP_HOSTED_HOST)/drivers/rpc/wrap                       \
    -I$(ESP_HOSTED_HOST)/drivers/serial                         \
    -I$(ESP_HOSTED_HOST)/drivers/virtual_serial_if/include      \
    -I$(ESP_HOSTED_HOST)/drivers/bt                             \
    \
    -I$(ESP_HOSTED_COMMON)                                      \
    -I$(ESP_HOSTED_COMMON)/log                                  \
    -I$(ESP_HOSTED_COMMON)/mempool/include                      \
    -I$(ESP_HOSTED_COMMON)/proto                                \
    -I$(ESP_HOSTED_COMMON)/protobuf-c/protobuf-c                \
    -I$(ESP_HOSTED_COMMON)/rpc                                  \
    -I$(ESP_HOSTED_COMMON)/transport                            \
    \
    -I$(LWIP_SRC)/include                                       \
    -I$(LWIP_DIR)/system                                        \
    -I$(LWIP_DIR)/system/arch

# =============================================================================
# Compiler Flags
# =============================================================================
HOST_CFLAGS = \
    -DESP_HOSTED_ENABLED           \
    -DCONFIG_ESP_HOSTED_SPI_HD_CUSTOM_MOSI_GPIO=0