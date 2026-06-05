/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Maps ESP-IDF error codes to standard C conventions
 */

#ifndef ESP_ERR_H
#define ESP_ERR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ESP Error Codes */
typedef int esp_err_t;

#define ESP_OK                          0x0
#define ESP_FAIL                        0x1

#define ESP_ERR_NO_MEM                  0x101
#define ESP_ERR_INVALID_ARG             0x102
#define ESP_ERR_INVALID_STATE           0x103
#define ESP_ERR_INVALID_SIZE            0x104
#define ESP_ERR_NOT_FOUND               0x105
#define ESP_ERR_NOT_SUPPORTED           0x106
#define ESP_ERR_TIMEOUT                 0x107
#define ESP_ERR_INVALID_RESPONSE        0x108
#define ESP_ERR_INVALID_CRC             0x109
#define ESP_ERR_INVALID_VERSION         0x10A
#define ESP_ERR_INVALID_MAC             0x10B
#define ESP_ERR_WIFI_BASE               0x3000
#define ESP_ERR_MESH_BASE               0x4000
#define ESP_ERR_FLASH_BASE              0x6000
#define ESP_ERR_HW_CRYPTO_BASE          0x6010
#define ESP_ERR_MEMPROT_BASE            0x6020
#define ESP_ERR_NVS_BASE                0x7000
#define ESP_ERR_MBEDTLS_CERT_BASE       0x8000
#define ESP_ERR_JSON_BASE               0x8100
#define ESP_ERR_ESPNOW_BASE             0x8C00
#define ESP_ERR_FREERTOS_BASE           0x8D00

/* Additional common error codes */
#define ESP_ERR_NOT_ALLOWED             0x110
#define ESP_ERR_NO_RESPONSE             0x111
#define ESP_ERR_NO_DATA                 0x112
#define ESP_ERR_BUFFER_FULL             0x113
#define ESP_ERR_NOT_FINISHED            0x114

/**
 * Check macro for error codes
 */
#define ESP_ERROR_CHECK(x) \
    do { esp_err_t rc = (x); if (rc != ESP_OK) { \
        __builtin_trap(); \
    } } while(0)

#ifdef __cplusplus
}
#endif

#endif /* ESP_ERR_H */
