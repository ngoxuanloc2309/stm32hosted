/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides power management
 */

#ifndef ESP_PM_H
#define ESP_PM_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PM_MODE_LIGHT_SLEEP,
    PM_MODE_MPS,
} esp_pm_lock_type_t;

typedef struct {} esp_pm_lock_handle_t;

/**
 * Acquire PM lock
 */
esp_err_t esp_pm_lock_create(esp_pm_lock_type_t type,
                            int arg,
                            const char* name,
                            esp_pm_lock_handle_t* out_handle);

/**
 * Release PM lock
 */
esp_err_t esp_pm_lock_delete(esp_pm_lock_handle_t handle);

/**
 * Acquire PM lock
 */
esp_err_t esp_pm_lock_acquire(esp_pm_lock_handle_t handle);

/**
 * Release PM lock
 */
esp_err_t esp_pm_lock_release(esp_pm_lock_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* ESP_PM_H */
