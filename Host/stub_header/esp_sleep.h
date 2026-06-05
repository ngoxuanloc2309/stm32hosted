/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides sleep/power management
 */

#ifndef ESP_SLEEP_H
#define ESP_SLEEP_H

#include "esp_err.h"
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ESP_SLEEP_WAKEUP_UNDEFINED,
    ESP_SLEEP_WAKEUP_ALL,
    ESP_SLEEP_WAKEUP_TIMER,
    ESP_SLEEP_WAKEUP_TOUCHPAD,
    ESP_SLEEP_WAKEUP_GPIO,
    ESP_SLEEP_WAKEUP_UART,
    ESP_SLEEP_WAKEUP_BT,
} esp_sleep_wakeup_cause_t;

/**
 * Enter deep sleep mode
 */
void esp_deep_sleep(uint64_t time_in_us) __attribute__((noreturn));

/**
 * Enter light sleep mode
 */
esp_err_t esp_light_sleep_start(void);

/**
 * Get sleep wakeup cause
 */
esp_sleep_wakeup_cause_t esp_sleep_get_wakeup_cause(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_SLEEP_H */
