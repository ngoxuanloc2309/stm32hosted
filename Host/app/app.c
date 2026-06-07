#include <stdio.h>
#include <string.h>
#include "app.h"
#include "app_config.h"
#include "ctrl_api.h"
#include "transport_drv.h"
#include "esp_netif.h"
#include "mqtt_service.h"
#include "user_mqtt.h"
#include "netdev_api.h"
#include "FreeRTOS.h"
#include "task.h"

static int wifi_connected = 0;
static volatile int s_transport_ready = 0;

/* ==== Event Callbacks ==== */
static int on_sta_connected(ctrl_cmd_t *event)
{
    printf("app: station connected\r\n");
    wifi_connected = 1;
    esp_netif_sta_up();
    CLEANUP_CTRL_MSG(event);
    return SUCCESS;
}

static int on_sta_disconnected(ctrl_cmd_t *event)
{
    printf("app: station disconnected\r\n");
    wifi_connected = 0;
    esp_netif_sta_down();
    CLEANUP_CTRL_MSG(event);
    return SUCCESS;
}

/* ==== Transport Event Handler ==== */
static void transport_event_handler(uint8_t event)
{
    switch (event) {
        case TRANSPORT_ACTIVE:
            printf("app: transport active\r\n");
            esp_netif_open();
            init_hosted_control_lib();
            set_event_callback(CTRL_EVENT_STATION_CONNECTED_TO_AP, on_sta_connected);
            set_event_callback(CTRL_EVENT_STATION_DISCONNECT_FROM_AP, on_sta_disconnected);
            s_transport_ready = 1;
            break;
        default:
            break;
    }
}

/* ==== WiFi Connect ==== */
static int wifi_connect(void)
{
    ctrl_cmd_t *req = (ctrl_cmd_t *)hosted_calloc(1, sizeof(ctrl_cmd_t));
    if (!req)
        return FAILURE;

    req->msg_type    = CTRL_REQ;
    req->msg_id      = CTRL_REQ_CONNECT_AP;
    req->cmd_timeout_sec = DEFAULT_CTRL_RESP_CONNECT_AP_TIMEOUT;

    strncpy((char *)req->u.wifi_ap_config.ssid,
            WIFI_SSID, SSID_LENGTH - 1);
    strncpy((char *)req->u.wifi_ap_config.pwd,
            WIFI_PASSWORD, PASSWORD_LENGTH - 1);
    req->u.wifi_ap_config.is_wpa3_supported = false;
    req->u.wifi_ap_config.listen_interval   = 3;

    ctrl_cmd_t *resp = wifi_connect_ap(req);
    if (!resp || resp->resp_event_status != SUCCESS) {
        printf("app: wifi_connect_ap failed\r\n");
        CLEANUP_CTRL_MSG(resp);
        return FAILURE;
    }

    CLEANUP_CTRL_MSG(resp);
    return SUCCESS;
}

/* ==== MQTT Task ==== */
static void mqtt_task(void *arg)
{
    while (!esp_netif_is_sta_connected())
        vTaskDelay(pdMS_TO_TICKS(1000));

    printf("app: IP assigned, starting MQTT\r\n");

    if (user_mqtt_start() != 0) {
        printf("app: MQTT start failed\r\n");
        vTaskDelete(NULL);
        return;
    }

    uint32_t count = 0;
    char payload[64];

    while (1) {
        snprintf(payload, sizeof(payload), "hello from synaptix #%lu", count++);
        user_mqtt_publish(MQTT_TOPIC_PUBLISH, payload);
        printf("app: published: %s\r\n", payload);

        for (int i = 0; i < 10; i++) {
            mqtt_service_process();
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

/* ==== app_main ==== */
void app_main(void)
{
    printf("app: starting\r\n");

    network_init();

    if (esp_netif_init() != 0) {
        printf("app: esp_netif_init failed\r\n");
        return;
    }

    transport_init(transport_event_handler);

    while (!s_transport_ready)
        vTaskDelay(pdMS_TO_TICKS(100));

    printf("app: transport ready, connecting wifi\r\n");

    if (wifi_connect() != 0) {
        printf("app: wifi_connect failed\r\n");
        return;
    }

    xTaskCreate(mqtt_task, "mqtt_task",
            MQTT_TASK_STACK_SIZE / sizeof(StackType_t),
            NULL, MQTT_TASK_PRIORITY, NULL);
}
