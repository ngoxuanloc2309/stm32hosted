/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides memory utilities
 */

#ifndef ESP_MEMORY_UTILS_H
#define ESP_MEMORY_UTILS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if address is in valid memory range
 */
int esp_memory_validate_address(void *addr, size_t len, int allow_flash);

/**
 * Get memory type for address
 */
int esp_memory_get_type(void *addr);

#ifdef __cplusplus
}
#endif

#endif /* ESP_MEMORY_UTILS_H */
