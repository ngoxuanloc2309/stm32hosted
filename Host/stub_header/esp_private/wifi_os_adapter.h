/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides WiFi OS adapter private definitions
 */

#ifndef WIFI_OS_ADAPTER_H
#define WIFI_OS_ADAPTER_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize WiFi OS adapter
 */
esp_err_t wifi_os_adapter_init(void);

/**
 * Deinit WiFi OS adapter
 */
esp_err_t wifi_os_adapter_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* WIFI_OS_ADAPTER_H */
