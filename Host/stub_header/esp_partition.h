/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides partition management
 */

#ifndef ESP_PARTITION_H
#define ESP_PARTITION_H

#include "esp_err.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Partition types */
typedef enum {
    ESP_PARTITION_TYPE_APP = 0x0,
    ESP_PARTITION_TYPE_DATA = 0x1,
} esp_partition_type_t;

/* Partition subtype */
typedef enum {
    ESP_PARTITION_SUBTYPE_DATA_OTA = 0x00,
    ESP_PARTITION_SUBTYPE_DATA_PHY = 0x01,
    ESP_PARTITION_SUBTYPE_DATA_NVS = 0x02,
    ESP_PARTITION_SUBTYPE_DATA_COREDUMP = 0x03,
    ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS = 0x04,
    ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM = 0x05,
} esp_partition_subtype_t;

/* Partition structure */
typedef struct {
    esp_partition_type_t type;
    esp_partition_subtype_t subtype;
    uint32_t address;
    uint32_t size;
    char label[16];
    uint32_t flags;
} esp_partition_t;

/**
 * Find partition
 */
const esp_partition_t* esp_partition_find_first(esp_partition_type_t type,
                                                esp_partition_subtype_t subtype,
                                                const char* label);

/**
 * Find next partition
 */
const esp_partition_t* esp_partition_find_next(const esp_partition_t* partition);

/**
 * Get partition iterator
 */
esp_err_t esp_partition_get(const esp_partition_t* partition);

/**
 * Read partition data
 */
esp_err_t esp_partition_read(const esp_partition_t* partition,
                            size_t src_offset, void* dst, size_t size);

/**
 * Write partition data
 */
esp_err_t esp_partition_write(const esp_partition_t* partition,
                             size_t target_offset, const void* src, size_t size);

/**
 * Erase partition range
 */
esp_err_t esp_partition_erase_range(const esp_partition_t* partition,
                                   uint32_t offset, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* ESP_PARTITION_H */
