#ifndef __USER_MQTT_H
#define __USER_MQTT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int  user_mqtt_start(void);
void user_mqtt_publish(const char *topic, const char *payload);
void user_mqtt_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* __USER_MQTT_H */