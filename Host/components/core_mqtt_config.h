#ifndef CORE_MQTT_CONFIG_H
#define CORE_MQTT_CONFIG_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define MQTT_STATE_ARRAY_MAX_COUNT      10
#define MQTT_RECV_POLLING_TIMEOUT_MS    0
#define MQTT_SEND_TIMEOUT_MS      400

#define LogError(x)     printf x
#define LogWarn(x)      printf x
#define LogInfo(x)      printf x
#define LogDebug(x)

#endif
