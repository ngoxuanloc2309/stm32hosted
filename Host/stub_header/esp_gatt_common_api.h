/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides GATT Common API
 */

#ifndef ESP_GATT_COMMON_API_H
#define ESP_GATT_COMMON_API_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Register GATT service
 */
esp_err_t esp_ble_gatts_create_attr_tab(void *gatt_db, void *gatts_if, uint16_t max_nb_attr, uint8_t srvc_instance_id);

/**
 * Start GATT service
 */
esp_err_t esp_ble_gatts_start_service(uint16_t service_handle);

#ifdef __cplusplus
}
#endif

#endif /* ESP_GATT_COMMON_API_H */
