/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides task definitions
 */

#ifndef ESP_TASK_H
#define ESP_TASK_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Task priorities */
#define ESP_TASK_PRIO_MAX       (configMAX_PRIORITIES)
#define ESP_TASK_PRIO_MIN       (0)

/* Task stack sizes */
#define ESP_TASK_STACK_SIZE_MIN     (1536)
#define ESP_TASK_STACK_SIZE_SMALL   (2048)
#define ESP_TASK_STACK_SIZE_MEDIUM  (4096)
#define ESP_TASK_STACK_SIZE_LARGE   (8192)

/* Main task priority */
#define ESP_TASK_MAIN_PRIO      (20)
#define ESP_TASK_MAIN_STACK     (4096)

/* Event loop task priority */
#define ESP_TASK_EVENT_PRIO     (20)
#define ESP_TASK_EVENT_STACK    (2048)

/* WiFi task priority */
#define ESP_TASK_WIFI_PRIO      (23)
#define ESP_TASK_WIFI_STACK     (3584)

/* Bluetooth task priority */
#define ESP_TASK_BT_PRIO        (21)
#define ESP_TASK_BT_STACK       (3072)

#ifdef __cplusplus
}
#endif

#endif /* ESP_TASK_H */
