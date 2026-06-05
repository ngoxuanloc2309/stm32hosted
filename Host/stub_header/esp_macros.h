/*
 * Stub header for ESP-Hosted MCU running on STM32
 * General macro definitions
 */

#ifndef ESP_MACROS_H
#define ESP_MACROS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Byte swapping macros */
#define SWAP_BYTES_16(x)    (((x) << 8) | (((x) >> 8) & 0xFF))
#define SWAP_BYTES_32(x)    ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) >> 8) & 0xFF00) | (((x) >> 24) & 0xFF))

/* Min/Max macros */
#ifndef MIN
#define MIN(a, b)           ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b)           ((a) > (b) ? (a) : (b))
#endif

/* Array size macro */
#define ARRAY_SIZE(arr)     (sizeof(arr) / sizeof((arr)[0]))

/* Container of macro */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))

/* Bit manipulation macros */
#define BIT(n)              (1 << (n))
#define BIT_MASK(n)         ((1 << (n)) - 1)

#ifdef __cplusplus
}
#endif

#endif /* ESP_MACROS_H */
