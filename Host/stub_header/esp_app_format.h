/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides application format
 */

#ifndef ESP_APP_FORMAT_H
#define ESP_APP_FORMAT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Application format constants */
#define ESP_IMAGE_HEADER_MAGIC  0xe9
#define ESP_IMAGE_MAX_SEGMENTS  16

/* Flash modes */
typedef enum {
    ESP_IMAGE_SPI_MODE_QIO   = 0,
    ESP_IMAGE_SPI_MODE_QOUT  = 1,
    ESP_IMAGE_SPI_MODE_DIO   = 2,
    ESP_IMAGE_SPI_MODE_DOUT  = 3,
} esp_image_spi_mode_t;

/* Flash frequency */
typedef enum {
    ESP_IMAGE_SPI_SPEED_40M = 0,
    ESP_IMAGE_SPI_SPEED_26M = 1,
    ESP_IMAGE_SPI_SPEED_20M = 2,
    ESP_IMAGE_SPI_SPEED_80M = 15,
} esp_image_spi_freq_t;

#ifdef __cplusplus
}
#endif

#endif /* ESP_APP_FORMAT_H */
