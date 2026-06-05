/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides logging macros compatible with ESP-IDF's logging system
 */

#ifndef ESP_LOG_H
#define ESP_LOG_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Log levels */
typedef enum {
    ESP_LOG_NONE,      /*!< No log output */
    ESP_LOG_ERROR,     /*!< Critical errors, software module can not recover on its own */
    ESP_LOG_WARN,      /*!< Error conditions from which recovery measures have been taken */
    ESP_LOG_INFO,      /*!< Information messages which describe normal flow of events */
    ESP_LOG_DEBUG,     /*!< Extra information which is not necessary for normal use (values, pointers, sizes, etc). */
    ESP_LOG_VERBOSE    /*!< Bigger chunks of debugging information, or frequent messages */
} esp_log_level_t;

/**
 * @brief Set log level for given tag
 *
 * @param tag Tag of the log entries to set the level for
 * @param level Desired logging level
 */
void esp_log_level_set(const char* tag, esp_log_level_t level);

/**
 * @brief Default log output function
 * Printf-like function which outputs to stdout/serial
 */
void esp_log_write(esp_log_level_t level, const char* tag, const char* format, ...);

/* Logging macros */
#define ESP_LOGE(tag, format, ...) esp_log_write(ESP_LOG_ERROR, tag, format, ##__VA_ARGS__)
#define ESP_LOGW(tag, format, ...) esp_log_write(ESP_LOG_WARN, tag, format, ##__VA_ARGS__)
#define ESP_LOGI(tag, format, ...) esp_log_write(ESP_LOG_INFO, tag, format, ##__VA_ARGS__)
#define ESP_LOGD(tag, format, ...) esp_log_write(ESP_LOG_DEBUG, tag, format, ##__VA_ARGS__)
#define ESP_LOGV(tag, format, ...) esp_log_write(ESP_LOG_VERBOSE, tag, format, ##__VA_ARGS__)

/* Simplified logging macros for minimal overhead */
#define ESP_LOG_ERROR(tag, format, ...)   ESP_LOGE(tag, format, ##__VA_ARGS__)
#define ESP_LOG_WARN(tag, format, ...)    ESP_LOGW(tag, format, ##__VA_ARGS__)
#define ESP_LOG_INFO(tag, format, ...)    ESP_LOGI(tag, format, ##__VA_ARGS__)
#define ESP_LOG_DEBUG(tag, format, ...)   ESP_LOGD(tag, format, ##__VA_ARGS__)
#define ESP_LOG_VERBOSE(tag, format, ...) ESP_LOGV(tag, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* ESP_LOG_H */
