/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides system functions
 */

#ifndef ESP_SYSTEM_H
#define ESP_SYSTEM_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the current system time in microseconds
 */
uint64_t esp_timer_get_time(void);

/**
 * Get version string
 */
const char* esp_get_idf_version(void);

/**
 * Restart the system
 */
void esp_restart(void) __attribute__((noreturn));

/**
 * System reset reason
 */
typedef enum {
    ESP_RST_UNKNOWN,
    ESP_RST_POWERON,
    ESP_RST_EXT,
    ESP_RST_SW,
    ESP_RST_PANIC,
    ESP_RST_INT_WDT,
    ESP_RST_TASK_WDT,
    ESP_RST_WDT,
    ESP_RST_DEEPSLEEP,
    ESP_RST_BROWNOUT,
    ESP_RST_SDIO,
    ESP_RST_USB_JTAG,
    ESP_RST_USB_UART,
    ESP_RST_USB_DEVICE,
} esp_reset_reason_t;

/**
 * Get the reset reason
 */
esp_reset_reason_t esp_reset_reason(void);

#ifdef __cplusplus
}
#endif

#endif /* ESP_SYSTEM_H */
