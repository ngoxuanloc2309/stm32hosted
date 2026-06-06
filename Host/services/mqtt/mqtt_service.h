#ifndef __MQTT_SERVICE_H
#define __MQTT_SERVICE_H

#include <stdint.h>
#include "core_mqtt.h"
#include "app_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mqtt_callback_t)(const char *topic, const uint8_t *payload, uint16_t len);

int  mqtt_service_init(void);
int  mqtt_service_connect(void);
void mqtt_service_disconnect(void);
int  mqtt_service_publish(const char *topic, const uint8_t *payload, uint16_t len, uint8_t qos);
int  mqtt_service_subscribe(const char *topic, uint8_t qos, mqtt_callback_t cb);
void mqtt_service_process(void);
int  mqtt_service_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif /* __MQTT_SERVICE_H */