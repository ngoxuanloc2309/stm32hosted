/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides cache operations
 */

#ifndef ESP_CACHE_H
#define ESP_CACHE_H

#include "esp_err.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Invalidate d-cache
 */
esp_err_t esp_cache_msync(void *addr, size_t len, int flags);

/**
 * Writeback and invalidate d-cache
 */
esp_err_t esp_cache_invalidate_addr_range(void *addr, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* ESP_CACHE_H */
