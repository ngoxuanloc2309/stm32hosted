/*
 * Stub implementation for ESP-Hosted MCU running on STM32
 * Provides basic logging functionality
 */

#include "esp_log.h"
#include "esp_system.h"
#include <stdarg.h>
#include <stdio.h>
#include "usart.h"
#include "stm32h5xx_hal.h"

/* Log level storage */
static esp_log_level_t s_log_level = ESP_LOG_INFO;

void esp_log_level_set(const char* tag, esp_log_level_t level)
{
    /* Simple implementation - set global log level */
    s_log_level = level;
}

void esp_log_write(esp_log_level_t level, const char* tag, const char* format, ...)
{
    va_list args;
    char buffer[512];
    int len = 0;

    /* Filter by log level */
    if (level > s_log_level) {
        return;
    }

    /* Add timestamp and tag */
    const char* level_str = "";
    switch (level) {
        case ESP_LOG_ERROR:   level_str = "E"; break;
        case ESP_LOG_WARN:    level_str = "W"; break;
        case ESP_LOG_INFO:    level_str = "I"; break;
        case ESP_LOG_DEBUG:   level_str = "D"; break;
        case ESP_LOG_VERBOSE: level_str = "V"; break;
        default:              level_str = "?"; break;
    }

    /* Format the message */
    va_start(args, format);
    len = snprintf(buffer, sizeof(buffer) - 1, "[%s] %s: ", level_str, tag);
    len += vsnprintf(buffer + len, sizeof(buffer) - len - 1, format, args);
    va_end(args);

    /* Add newline */
    if (len < (int)sizeof(buffer) - 1) {
        buffer[len++] = '\n';
    }
    buffer[len] = '\0';

    /* Output to UART2 */
    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, HAL_MAX_DELAY);
}

/* Stub functions for other esp_log features */
uint64_t esp_timer_get_time(void)
{
    /* Return milliseconds converted to microseconds */
    return HAL_GetTick() * 1000;
}

esp_reset_reason_t esp_reset_reason(void)
{
    return ESP_RST_UNKNOWN;
}

const char* esp_get_idf_version(void)
{
    return "5.4.3-stm32-stub";
}

void esp_restart(void)
{
    NVIC_SystemReset();
    while (1);
}
