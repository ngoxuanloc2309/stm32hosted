/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides DMA utilities
 */

#ifndef ESP_DMA_UTILS_H
#define ESP_DMA_UTILS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Check if memory is DMA-capable
 */
int esp_dma_capable_p(void* ptr);

/**
 * Allocate DMA-capable memory
 */
void* esp_dma_malloc(size_t size);

/**
 * Free DMA memory
 */
void esp_dma_free(void* ptr);

/**
 * Get maximum DMA chunk size
 */
size_t esp_dma_get_max_chunk_size(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_DMA_UTILS_H */
