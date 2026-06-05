/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides memory management functions
 */

#ifndef ESP_HEAP_CAPS_H
#define ESP_HEAP_CAPS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Heap capability flags */
#define MALLOC_CAP_EXEC        (1 << 0)
#define MALLOC_CAP_32BIT       (1 << 1)
#define MALLOC_CAP_8BIT        (1 << 2)
#define MALLOC_CAP_DMA         (1 << 3)
#define MALLOC_CAP_PID2        (1 << 4)
#define MALLOC_CAP_PID3        (1 << 5)
#define MALLOC_CAP_PID4        (1 << 6)
#define MALLOC_CAP_PID5        (1 << 7)
#define MALLOC_CAP_PID6        (1 << 8)
#define MALLOC_CAP_PID7        (1 << 9)
#define MALLOC_CAP_SPIRAM      (1 << 10)
#define MALLOC_CAP_INTERNAL    (1 << 11)
#define MALLOC_CAP_DEFAULT     (1 << 12)

/**
 * Allocate memory with capability requirements
 */
void* heap_caps_malloc(size_t size, uint32_t caps);

/**
 * Free memory allocated with heap_caps_malloc
 */
void heap_caps_free(void* ptr);

/**
 * Reallocate memory
 */
void* heap_caps_realloc(void* ptr, size_t size, uint32_t caps);

/**
 * Get free heap size with specific capability
 */
size_t heap_caps_get_free_size(uint32_t caps);

/**
 * Get total heap size with specific capability
 */
size_t heap_caps_get_total_size(uint32_t caps);

/**
 * Largest continuous free block
 */
size_t heap_caps_get_largest_free_block(uint32_t caps);

#ifdef __cplusplus
}
#endif

#endif /* ESP_HEAP_CAPS_H */
