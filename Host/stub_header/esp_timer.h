/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides timer functions
 */

#ifndef ESP_TIMER_H
#define ESP_TIMER_H

#include "esp_err.h"
#include <stdint.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t esp_timer_handle_t;

typedef void (*esp_timer_callback_t)(void* arg);

/**
 * Create a timer
 */
esp_err_t esp_timer_create(const struct {
    esp_timer_callback_t callback;
    void* arg;
    const char* name;
    uint32_t skip_unhandled_events;
} *create_args, esp_timer_handle_t* out_handle);

/**
 * Delete a timer
 */
esp_err_t esp_timer_delete(esp_timer_handle_t timer);

/**
 * Start a timer
 */
esp_err_t esp_timer_start_periodic(esp_timer_handle_t timer, uint64_t period);

/**
 * Stop a timer
 */
esp_err_t esp_timer_stop(esp_timer_handle_t timer);

/**
 * Get current time in microseconds
 */
uint64_t esp_timer_get_time(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_TIMER_H */
