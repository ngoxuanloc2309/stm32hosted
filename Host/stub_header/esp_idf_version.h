/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Defines version information
 */

#ifndef ESP_IDF_VERSION_H
#define ESP_IDF_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

/* Version numbers */
#define ESP_IDF_VERSION_MAJOR       5
#define ESP_IDF_VERSION_MINOR       4
#define ESP_IDF_VERSION_PATCH       3

#define ESP_IDF_VERSION ((ESP_IDF_VERSION_MAJOR << 16) | (ESP_IDF_VERSION_MINOR << 8) | ESP_IDF_VERSION_PATCH)

/* Version string */
#define ESP_IDF_VERSION_STR "5.4.3-stm32-stub"

/**
 * Macro to check version at compile time
 */
#define ESP_IDF_VERSION_CHECK(major, minor, patch) \
    (ESP_IDF_VERSION >= (((major) << 16) | ((minor) << 8) | (patch)))

#ifdef __cplusplus
}
#endif

#endif /* ESP_IDF_VERSION_H */
