/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides Bluetooth GATT API
 */

#ifndef ESP_GATT_DEFS_H
#define ESP_GATT_DEFS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* GATT error codes */
typedef enum {
    ESP_GATT_OK = 0x0,
    ESP_GATT_INVALID_HANDLE = 0x1,
    ESP_GATT_READ_NOT_PERMIT = 0x2,
    ESP_GATT_WRITE_NOT_PERMIT = 0x3,
    ESP_GATT_INVALID_PDU = 0x4,
    ESP_GATT_INSUF_AUTHENTICATION = 0x5,
    ESP_GATT_REQ_NOT_SUPPORTED = 0x6,
    ESP_GATT_INVALID_OFFSET = 0x7,
    ESP_GATT_INSUF_AUTHORIZATION = 0x8,
    ESP_GATT_PREPARE_Q_FULL = 0x9,
    ESP_GATT_ATTR_NOT_FOUND = 0xa,
    ESP_GATT_ATTR_NOT_LONG = 0xb,
} esp_gatt_status_t;

/* GATT attribute types */
#define ESP_UUID_LEN_16     2
#define ESP_UUID_LEN_32     4
#define ESP_UUID_LEN_128    16

typedef struct {
    uint8_t len;
    uint8_t uuid[16];
} esp_bt_uuid_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP_GATT_DEFS_H */
