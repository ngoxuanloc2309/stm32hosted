## 🚀 Hướng Dẫn Tích Hợp ESP-Hosted MCU Stub Headers

### 📋 Mục Đích

Tài liệu này hướng dẫn cách sử dụng stub headers để port **ESP-Hosted MCU** từ ESP32 sang **STM32H563**.

### 📦 Cấu Trúc Đã Chuẩn Bị

```
Host/
├── stub_header/          # ESP-IDF compatibility layer
│   ├── esp_*.h           # Stub headers
│   ├── esp_private/      # Private headers
│   ├── esp_log_impl.c    # Implementation for logging
│   └── README.md         # Documentation
├── lib/
│   └── esp-hosted-mcu/   # ESP-Hosted MCU source
├── port/                 # STM32H5 HAL wrappers
├── services/             # Application services
└── app/                  # Application code
```

### ✅ Các Bước Tích Hợp

#### 1️⃣ **Cấu Hình Build System**

**Makefile được cập nhật tự động với:**

```makefile
# Stub header sources
STUB_HEADER_FILES = \
    $(HOST_DIR)/stub_header/esp_log_impl.c

# Include paths (stub_header ở đầu tiên)
HOST_INCLUDES = \
    -I$(HOST_DIR)/stub_header                # ← Ưu tiên cao
    -I$(HOST_DIR)/app
    ...
```

#### 2️⃣ **Thử Biên Dịch Đầu Tiên**

```bash
cd d:\Synaptix\SynaptiX\esp32_stm32\host_newgen
make clean
make
```

**Các lỗi có thể gặp:**
- `undefined reference to 'esp_*'` → Implement function trong `esp_log_impl.c`
- `no such file or directory` → Kiểm tra include paths

#### 3️⃣ **Xử Lý Lỗi Biên Dịch**

**Nếu gặp lỗi undefined reference:**

```c
// Thêm implement vào esp_log_impl.c hoặc tạo file mới

esp_err_t esp_wifi_init(const void* config)
{
    ESP_LOGI("esp_wifi", "WiFi init stub - not implemented");
    return ESP_OK;
}
```

**Nếu header khác bị thiếu:**

Tạo file mới trong `Host/stub_header/`:
```bash
touch Host/stub_header/esp_new_header.h
```

#### 4️⃣ **Testing Logging**

```c
// Trong Core/Src/main.c hoặc app file
#include "esp_log.h"

int main(void) {
    MX_USART2_UART_Init();
    
    ESP_LOGI("MAIN", "Initialization started");
    ESP_LOGW("MAIN", "Warning message");
    ESP_LOGE("MAIN", "Error detected");
    
    // Code của bạn...
}
```

**Output trên serial (UART2):**
```
[I] MAIN: Initialization started
[W] MAIN: Warning message
[E] MAIN: Error detected
```

### 🔧 Các Function Đã Implement

| Function | Location | Status |
|----------|----------|--------|
| `esp_log_write()` | `esp_log_impl.c` | ✅ Implemented |
| `esp_log_level_set()` | `esp_log_impl.c` | ✅ Implemented |
| `esp_timer_get_time()` | `esp_log_impl.c` | ✅ Implemented |
| `esp_get_idf_version()` | `esp_log_impl.c` | ✅ Implemented |
| `esp_reset_reason()` | `esp_log_impl.c` | ✅ Implemented |
| `esp_restart()` | `esp_log_impl.c` | ✅ Implemented |
| Các function khác | stub headers | ⚠️ Stubs only |

### 🛠️ Mở Rộng & Customization

#### Thay Đổi UART Logging

Sửa trong `esp_log_impl.c`:
```c
// Hiện tại:
HAL_UART_Transmit(&huart2, (uint8_t*)buffer, len, HAL_MAX_DELAY);

// Thay thành UART3:
HAL_UART_Transmit(&huart3, (uint8_t*)buffer, len, HAL_MAX_DELAY);
```

#### Implement Thêm Functions

**Bước 1**: Kiểm tra header có declaration chưa
```bash
grep -n "esp_wifi_init" Host/stub_header/esp_wifi.h
```

**Bước 2**: Nếu chưa, thêm vào header
```c
// esp_wifi.h
esp_err_t esp_wifi_init(const void* config);
```

**Bước 3**: Implement trong `esp_log_impl.c` hoặc tạo file mới
```c
// esp_log_impl.c
esp_err_t esp_wifi_init(const void* config)
{
    ESP_LOGI("wifi", "WiFi initialized on STM32");
    return ESP_OK;
}
```

### ⚠️ Lưu Ý Quan Trọng

1. **UART Hard-coded**: Logging mặc định sử dụng UART2, cần init trước khi log
2. **FreeRTOS Dependency**: Các macros như `ESP_TASK_PRIO_MAX` phụ thuộc vào FreeRTOS config
3. **Memory**: Buffer logging có size 512 bytes, điều chỉnh nếu cần
4. **No Real WiFi**: WiFi functions chỉ là stubs, cần implement hoặc port từ ESP-IDF

### 📝 Danh Sách Headers Được Cung Cấp

**Core:**
- ✅ `esp_err.h` - Error codes
- ✅ `esp_log.h` - Logging
- ✅ `esp_check.h` - Assertions
- ✅ `esp_idf_version.h` - Version info

**System:**
- ✅ `esp_system.h` - System functions
- ✅ `esp_timer.h` - Timer stubs
- ✅ `esp_event.h` - Event stubs
- ✅ `esp_sleep.h` - Sleep stubs
- ✅ `esp_pm.h` - Power management stubs

**Memory & Utils:**
- ✅ `esp_heap_caps.h` - Memory allocation
- ✅ `esp_memory_utils.h` - Memory utilities
- ✅ `esp_cache.h` - Cache operations
- ✅ `esp_dma_utils.h` - DMA utilities
- ✅ `esp_attr.h` - Compiler attributes
- ✅ `esp_macros.h` - Utility macros

**Networking:**
- ✅ `esp_wifi.h` - WiFi API (stubs)
- ✅ `esp_wifi_types.h` - WiFi types
- ✅ `esp_wifi_default.h` - WiFi defaults
- ✅ `esp_wifi_he.h` - WiFi 802.11ax (stubs)
- ✅ `esp_wifi_remote.h` - WiFi remote (stubs)
- ✅ `esp_netif.h` - Network interface (stubs)
- ✅ `esp_netif_types.h` - Network types

**Bluetooth:**
- ✅ `esp_bt.h` - Bluetooth API (stubs)
- ✅ `esp_mac.h` - MAC address (stubs)
- ✅ `esp_gatt_defs.h` - GATT definitions
- ✅ `esp_gap_ble_api.h` - BLE GAP (stubs)
- ✅ `esp_gatt_common_api.h` - GATT common (stubs)

**Storage & Other:**
- ✅ `esp_partition.h` - Partition management (stubs)
- ✅ `esp_app_desc.h` - App descriptor (stubs)
- ✅ `esp_app_format.h` - App format (stubs)
- ✅ `esp_console.h` - Console (stubs)
- ✅ `esp_event_base.h` - Event base definitions
- ✅ `esp_task.h` - Task definitions
- ✅ `esp_private/wifi_os_adapter.h` - Private adapter (stubs)

### 🚨 Troubleshooting

| Vấn Đề | Giải Pháp |
|--------|----------|
| `undefined reference to 'esp_log_write'` | Kiểm tra `esp_log_impl.c` có trong build không |
| Không thấy log output | Kiểm tra UART2 init, baud rate, kết nối cable |
| Compile error: header not found | Kiểm tra `-I$(HOST_DIR)/stub_header` ở đầu C_INCLUDES |
| Link error | Thêm function declaration vào header + implement |

### 📚 Tài Liệu Liên Quan

- [ESP-IDF API Reference](https://docs.espressif.com/projects/esp-idf/en/stable/api-reference/)
- [STM32H563 HAL Documentation](https://www.st.com/)
- [ESP-Hosted MCU GitHub](https://github.com/espressif/esp-hosted-mcu)
- [Makefile Documentation](../host.mk)

### 💡 Tips & Tricks

1. **Debug Logging**: Tăng log level để debug
   ```c
   esp_log_level_set("*", ESP_LOG_VERBOSE);
   ```

2. **Custom Tags**: Sử dụng tags để filter messages
   ```c
   ESP_LOGI("MY_TAG", "Custom message");
   esp_log_level_set("MY_TAG", ESP_LOG_DEBUG);
   ```

3. **Performance**: Disable logging in release build
   ```makefile
   # Trong Makefile
   C_DEFS += -DESP_LOG_LEVEL_NONE
   ```

### 📞 Support

Nếu gặp vấn đề:
1. Kiểm tra log output trên serial
2. Xem Makefile configuration
3. Kiểm tra include paths
4. Đọc source code trong stub_header/
