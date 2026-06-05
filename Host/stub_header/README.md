## ESP-Hosted MCU Stub Headers for STM32

Thư mục này chứa các stub header files để thay thế các ESP-IDF dependencies khi port ESP-Hosted MCU sang STM32.

### 📋 Danh sách các Stub Headers

#### Core Headers (Thiết yếu)
- **esp_err.h** - Error codes system
  - Định nghĩa `esp_err_t` và các error codes
  - Provides `ESP_ERROR_CHECK()` macro

- **esp_log.h** - Logging system
  - Defines `ESP_LOGE()`, `ESP_LOGW()`, `ESP_LOGI()`, `ESP_LOGD()`, `ESP_LOGV()`
  - Implementation: `esp_log_impl.c` - outputs to UART1

- **esp_check.h** - Assertion macros
  - `ESP_RETURN_ON_FALSE()`, `ESP_RETURN_ON_ERROR()`
  - `ESP_GOTO_ON_FALSE()`, `ESP_GOTO_ON_ERROR()`

#### System Headers
- **esp_idf_version.h** - Version information
- **esp_attr.h** - Compiler attributes (ALIGNED, PACKED, etc.)
- **esp_macros.h** - General macros (MIN, MAX, ARRAY_SIZE, etc.)
- **esp_system.h** - System functions
  - `esp_timer_get_time()`, `esp_get_idf_version()`, `esp_restart()`
  - `esp_reset_reason()`

#### Platform Headers
- **esp_timer.h** - Timer functions (minimal stubs)
- **esp_event.h** - Event system (minimal stubs)
- **esp_sleep.h** - Sleep/power management (minimal stubs)
- **esp_pm.h** - Power management (minimal stubs)

#### Memory Headers
- **esp_heap_caps.h** - Memory allocation with capabilities
  - `heap_caps_malloc()`, `heap_caps_free()`, `heap_caps_realloc()`

#### Networking Headers
- **esp_wifi.h** - WiFi API
- **esp_wifi_types.h** - WiFi types and structures
- **esp_netif.h** - Network interface API
- **esp_netif_types.h** - Network types

#### Bluetooth Headers
- **esp_bt.h** - Bluetooth API (minimal stubs)
- **esp_mac.h** - MAC address operations
- **esp_task.h** - Task/Thread priorities

#### Other Headers
- **esp_partition.h** - Partition management (flash)
- **esp_console.h** - Console command system
- **esp_event_base.h** - Event base definitions
- **esp_private/wifi_os_adapter.h** - Private WiFi OS adapter

### 🔧 Cách Sử Dụng

1. **Đã include tự động**: Các header này được thêm vào include paths trong `host.mk`:
   ```makefile
   -I$(HOST_DIR)/stub_header
   ```

2. **Ưu tiên include**: Stub headers sẽ được include trước, thay thế bất kỳ headers từ ESP-IDF nào.

3. **Implementation**: Một số functions được implement sẵn trong `esp_log_impl.c`:
   - `esp_log_write()` - Outputs to UART1 (STM32H5)
   - `esp_timer_get_time()` - Uses HAL_GetTick()
   - `esp_restart()` - NVIC system reset

### 🚀 Mở Rộng

Nếu cần implement thêm functions, hãy:

1. **Thêm declaration** vào header file tương ứng (nếu chưa có)
2. **Implement function** trong một `.c` file hoặc thêm vào `esp_log_impl.c`
3. **Thêm source file** vào `STUB_HEADER_FILES` trong `host.mk` nếu tạo file mới

#### Ví dụ Implementation

Nếu cần implement `esp_wifi_init()`:

```c
// Trong esp_wifi.h (đã có)
esp_err_t esp_wifi_init(const void* config);

// Thêm implement trong file riêng hoặc esp_log_impl.c
esp_err_t esp_wifi_init(const void* config)
{
    ESP_LOGI("esp_wifi", "WiFi initialized");
    return ESP_OK;
}
```

### ⚠️ Lưu Ý

1. **Minimal Implementation**: Nhiều functions chỉ là stubs và trả về `ESP_OK` hoặc values mặc định
2. **UART1 Hardcoded**: Logging hiện sử dụng UART1 (STM32H563), có thể thay đổi trong `esp_log_impl.c`
3. **FreeRTOS Dependency**: Các functions sử dụng FreeRTOS (ví dụ, task priorities) giả định FreeRTOS đã được configure
4. **HAL Dependency**: Một số functions sử dụng STM32H5xx HAL (ví dụ, `HAL_GetTick()`, `NVIC_SystemReset()`)

### 📝 Cấu Trúc Thư Mục

```
Host/stub_header/
├── esp_*.h                    # Main stub headers
├── esp_log_impl.c             # Implementation for logging and system functions
├── esp_private/
│   └── wifi_os_adapter.h      # Private WiFi OS adapter
└── README.md                  # Tệp này
```

### 🔗 Liên Kết

- [ESP-IDF Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [STM32H563 HAL Documentation](https://www.st.com/resource/en/datasheet/stm32h563.pdf)
- [ESP-Hosted MCU Repository](https://github.com/espressif/esp-hosted-mcu)
