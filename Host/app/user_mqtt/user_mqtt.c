#include <string.h>
#include <stdio.h>
#include "user_mqtt.h"
#include "mqtt_service.h"
#include "app_config.h"
#include "FreeRTOS.h"
#include "task.h"

static void on_message(const char *topic, const uint8_t *payload, uint16_t len)
{
    printf("rx [%s]: %.*s\r\n", topic, len, payload);
}

int user_mqtt_start(void)
{
    if (mqtt_service_init() != 0) {
        printf("user_mqtt: init failed\r\n");
        return -1;
    }

    int retry = 5;
    while (retry--) {
        if (mqtt_service_connect() == 0)
            break;
        printf("user_mqtt: retry connect...\r\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    if (!mqtt_service_is_connected()) {
        printf("user_mqtt: connect failed\r\n");
        return -1;
    }

    mqtt_service_subscribe(MQTT_TOPIC_SUBSCRIBE, 0, on_message);
    return 0;
}

void user_mqtt_publish(const char *topic, const char *payload)
{
    if (!mqtt_service_is_connected())
        return;
    mqtt_service_publish(topic, (const uint8_t *)payload, strlen(payload), 0);
}

void user_mqtt_stop(void)
{
    mqtt_service_disconnect();
}