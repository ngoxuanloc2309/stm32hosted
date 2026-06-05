/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides application descriptor
 */

#ifndef ESP_APP_DESC_H
#define ESP_APP_DESC_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Application descriptor */
typedef struct {
    uint32_t magic_number;
    uint32_t segment_table_offset;
    uint32_t segment_count;
    uint32_t flash_mode;
    uint32_t flash_size_freq;
    uint32_t flash_size_freq;
    uint32_t version;
    uint8_t app_elf_sha256[32];
    uint32_t secure_pad;
    uint32_t secure_version;
} esp_app_desc_t;

/**
 * Get app descriptor
 */
const esp_app_desc_t *esp_app_get_description(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_APP_DESC_H */
