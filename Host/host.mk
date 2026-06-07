# ==== Base Paths ====
HOST_DIR        = Host
LIBS_DIR        = $(HOST_DIR)/libs
ESP_HOSTED_DIR  = $(LIBS_DIR)/esp-hosted/esp_hosted_fg
ESP_STM32_DIR   = $(ESP_HOSTED_DIR)/host/stm32
LWIP_DIR        = $(LIBS_DIR)/lwip
COREMQTT_DIR    = $(LIBS_DIR)/coreMQTT

# ==== Host Sources ====
HOST_SOURCES = \
$(HOST_DIR)/port/stm32h5/platform_wrapper.c \
$(HOST_DIR)/components/netif/esp_netif.c \
$(HOST_DIR)/components/cmsis_os_compat.c \
$(HOST_DIR)/services/mqtt/mqtt_service.c \
$(HOST_DIR)/app/user_mqtt/user_mqtt.c \
$(HOST_DIR)/app/app.c \
\
$(ESP_STM32_DIR)/common/common.c \
$(ESP_STM32_DIR)/common/util.c \
$(ESP_STM32_DIR)/common/stats.c \
$(ESP_STM32_DIR)/driver/transport/spi/spi_drv.c \
$(ESP_STM32_DIR)/driver/transport/transport_drv.c \
$(ESP_STM32_DIR)/driver/network/netdev_api.c \
$(ESP_STM32_DIR)/driver/network/netdev_stub.c \
$(ESP_STM32_DIR)/driver/serial/serial_ll_if.c \
$(ESP_HOSTED_DIR)/host/virtual_serial_if/src/serial_if.c \
$(ESP_HOSTED_DIR)/host/components/src/esp_queue.c \
$(ESP_HOSTED_DIR)/host/control_lib/src/ctrl_api.c \
$(ESP_HOSTED_DIR)/host/control_lib/src/ctrl_core.c \
$(ESP_HOSTED_DIR)/common/esp_hosted_config.pb-c.c \
$(ESP_HOSTED_DIR)/common/protobuf-c/protobuf-c/protobuf-c.c \
\
$(LWIP_DIR)/src/core/init.c \
$(LWIP_DIR)/src/core/def.c \
$(LWIP_DIR)/src/core/dns.c \
$(LWIP_DIR)/src/core/inet_chksum.c \
$(LWIP_DIR)/src/core/ip.c \
$(LWIP_DIR)/src/core/mem.c \
$(LWIP_DIR)/src/core/memp.c \
$(LWIP_DIR)/src/core/netif.c \
$(LWIP_DIR)/src/core/pbuf.c \
$(LWIP_DIR)/src/core/raw.c \
$(LWIP_DIR)/src/core/stats.c \
$(LWIP_DIR)/src/core/sys.c \
$(LWIP_DIR)/src/core/altcp.c \
$(LWIP_DIR)/src/core/altcp_alloc.c \
$(LWIP_DIR)/src/core/altcp_tcp.c \
$(LWIP_DIR)/src/core/tcp.c \
$(LWIP_DIR)/src/core/tcp_in.c \
$(LWIP_DIR)/src/core/tcp_out.c \
$(LWIP_DIR)/src/core/timeouts.c \
$(LWIP_DIR)/src/core/udp.c \
$(LWIP_DIR)/src/core/ipv4/autoip.c \
$(LWIP_DIR)/src/core/ipv4/dhcp.c \
$(LWIP_DIR)/src/core/ipv4/etharp.c \
$(LWIP_DIR)/src/core/ipv4/icmp.c \
$(LWIP_DIR)/src/core/ipv4/igmp.c \
$(LWIP_DIR)/src/core/ipv4/ip4.c \
$(LWIP_DIR)/src/core/ipv4/ip4_addr.c \
$(LWIP_DIR)/src/core/ipv4/ip4_frag.c \
$(LWIP_DIR)/src/netif/ethernet.c \
$(LWIP_DIR)/src/netif/bridgeif.c \
$(LWIP_DIR)/src/netif/bridgeif_fdb.c \
$(LWIP_DIR)/src/netif/slipif.c \
$(LWIP_DIR)/src/api/api_lib.c \
$(LWIP_DIR)/src/api/api_msg.c \
$(LWIP_DIR)/src/api/err.c \
$(LWIP_DIR)/src/api/if_api.c \
$(LWIP_DIR)/src/api/netbuf.c \
$(LWIP_DIR)/src/api/netdb.c \
$(LWIP_DIR)/src/api/netifapi.c \
$(LWIP_DIR)/src/api/sockets.c \
$(LWIP_DIR)/src/api/tcpip.c \
$(LWIP_DIR)/system/OS/sys_arch.c \
$(LWIP_DIR)/src/core/ipv4/acd.c \
\
$(COREMQTT_DIR)/source/core_mqtt.c \
$(COREMQTT_DIR)/source/core_mqtt_serializer.c \
$(COREMQTT_DIR)/source/core_mqtt_state.c \
$(COREMQTT_DIR)/source/core_mqtt_prop_deserializer.c \
$(COREMQTT_DIR)/source/core_mqtt_prop_serializer.c \
$(COREMQTT_DIR)/source/core_mqtt_serializer_private.c \

# ==== Host Includes ====
HOST_INCLUDES = \
-I$(HOST_DIR)/app \
-I$(HOST_DIR)/app/user_mqtt \
-I$(HOST_DIR)/port/stm32h5 \
-I$(HOST_DIR)/components \
-I$(HOST_DIR)/components/netif \
-I$(HOST_DIR)/services/mqtt \
\
-I$(ESP_STM32_DIR)/common \
-I$(ESP_STM32_DIR)/driver/transport \
-I$(ESP_STM32_DIR)/driver/transport/spi \
-I$(ESP_STM32_DIR)/driver/network \
-I$(ESP_STM32_DIR)/driver/netif \
-I$(ESP_STM32_DIR)/driver/serial \
-I$(ESP_STM32_DIR)/port/include \
-I$(ESP_HOSTED_DIR)/common/include \
-I$(ESP_HOSTED_DIR)/common/protobuf-c \
-I$(ESP_HOSTED_DIR)/host/virtual_serial_if/include \
-I$(ESP_HOSTED_DIR)/host/components/include \
-I$(ESP_HOSTED_DIR)/host/control_lib/include \
-I$(ESP_HOSTED_DIR)/host/control_lib/src/include \
\
-I$(LWIP_DIR)/src/include \
-I$(LWIP_DIR)/system \
-I$(LWIP_DIR)/system/arch \
\
-I$(COREMQTT_DIR)/source/include \
-I$(COREMQTT_DIR)/source/interface \
-I$(HOST_DIR)/../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 

HOST_CFLAGS += -include $(HOST_DIR)/components/cmsis_os_compat.h 
HOST_CFLAGS += -D__NETDEV_PBUF_DEFINED__ 
