/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Provides BLE GAP API
 */

#ifndef ESP_GAP_BLE_API_H
#define ESP_GAP_BLE_API_H

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/* BLE advertising types */
typedef enum {
    ADV_TYPE_IND = 0x00,
    ADV_TYPE_DIRECT_IND_HIGH = 0x01,
    ADV_TYPE_SCAN_IND = 0x02,
    ADV_TYPE_NONCONN_IND = 0x03,
    ADV_TYPE_DIRECT_IND_LOW = 0x04,
} esp_ble_adv_type_t;

/* BLE advertising channel */
typedef enum {
    ADV_CHNL_37 = 0x01,
    ADV_CHNL_38 = 0x02,
    ADV_CHNL_39 = 0x04,
    ADV_CHNL_ALL = 0x07,
} esp_ble_adv_channel_t;

/**
 * Set raw advertise data
 */
esp_err_t esp_ble_gap_config_adv_data(void *data);

/**
 * Start BLE advertising
 */
esp_err_t esp_ble_gap_start_advertising(void *adv_params);

/**
 * Stop BLE advertising
 */
esp_err_t esp_ble_gap_stop_advertising(void);

/**
 * Set scan response data
 */
esp_err_t esp_ble_gap_config_scan_rsp_data(void *data);

#ifdef __cplusplus
}
#endif

#endif /* ESP_GAP_BLE_API_H */
