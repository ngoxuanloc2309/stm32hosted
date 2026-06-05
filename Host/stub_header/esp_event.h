/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides event system
 */

#ifndef ESP_EVENT_H
#define ESP_EVENT_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int32_t source;
    int32_t event_id;
} esp_event_base_t;

typedef void (*esp_event_handler_t)(void* event_handler_arg, esp_event_base_t event_base, int32_t event_id, void* event_data);

/**
 * Create default event loop
 */
esp_err_t esp_event_loop_create_default(void);

/**
 * Delete default event loop
 */
esp_err_t esp_event_loop_delete_default(void);

/**
 * Register event handler
 */
esp_err_t esp_event_handler_register(esp_event_base_t event_base,
                                     int32_t event_id,
                                     esp_event_handler_t event_handler,
                                     void* event_handler_arg);

/**
 * Unregister event handler
 */
esp_err_t esp_event_handler_unregister(esp_event_base_t event_base,
                                       int32_t event_id,
                                       esp_event_handler_t event_handler);

/**
 * Post event to the event loop
 */
esp_err_t esp_event_post(esp_event_base_t event_base,
                        int32_t event_id,
                        void* event_data,
                        size_t event_data_size,
                        int ticks_to_wait);

#ifdef __cplusplus
}
#endif

#endif /* ESP_EVENT_H */
