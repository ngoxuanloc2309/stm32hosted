/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides assertion and check macros
 */

#ifndef ESP_CHECK_H
#define ESP_CHECK_H

#include "esp_err.h"
#include "esp_log.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Assertion check macros
 */
#define ESP_RETURN_ON_FALSE(condition, err, tag, format, ...) \
    do { \
        if (!(condition)) { \
            ESP_LOGE(tag, format, ##__VA_ARGS__); \
            return err; \
        } \
    } while(0)

#define ESP_RETURN_ON_ERROR(x, tag, format, ...) \
    do { \
        esp_err_t err = (x); \
        if (err != ESP_OK) { \
            ESP_LOGE(tag, format, ##__VA_ARGS__); \
            return err; \
        } \
    } while(0)

#define ESP_GOTO_ON_FALSE(condition, err, label, tag, format, ...) \
    do { \
        if (!(condition)) { \
            ESP_LOGE(tag, format, ##__VA_ARGS__); \
            goto label; \
        } \
    } while(0)

#define ESP_GOTO_ON_ERROR(x, label, tag, format, ...) \
    do { \
        esp_err_t err = (x); \
        if (err != ESP_OK) { \
            ESP_LOGE(tag, format, ##__VA_ARGS__); \
            goto label; \
        } \
    } while(0)

#ifdef __cplusplus
}
#endif

#endif /* ESP_CHECK_H */
