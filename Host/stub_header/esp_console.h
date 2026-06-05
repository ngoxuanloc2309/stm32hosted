/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides console command API
 */

#ifndef ESP_CONSOLE_H
#define ESP_CONSOLE_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*esp_console_cmd_func_t)(int argc, char** argv);

typedef struct {
    const char *command;
    const char *help;
    esp_console_cmd_func_t func;
} esp_console_cmd_t;

/**
 * Initialize console
 */
esp_err_t esp_console_dev_uart_set_rx_line_endings(int endings);

/**
 * Set console TX line endings
 */
esp_err_t esp_console_dev_uart_set_tx_line_endings(int endings);

/**
 * Initialize console
 */
esp_err_t esp_console_init(const void* config);

/**
 * Register console command
 */
esp_err_t esp_console_cmd_register(const esp_console_cmd_t *cmd);

/**
 * Run console
 */
esp_err_t esp_console_run(const char *cmdline, int *cmd_ret);

#ifdef __cplusplus
}
#endif

#endif /* ESP_CONSOLE_H */
