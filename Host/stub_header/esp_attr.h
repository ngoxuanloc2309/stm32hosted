/*
 * Stub header for ESP-Hosted MCU running on STM32
 * Defines compiler attributes
 */

#ifndef ESP_ATTR_H
#define ESP_ATTR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Attributes for different architectures */
#if defined(__GNUC__)
    #define ALIGNED(x)              __attribute__((aligned(x)))
    #define PACKED                  __attribute__((packed))
    #define ALWAYS_INLINE           inline __attribute__((always_inline))
    #define NO_INLINE               __attribute__((noinline))
    #define WEAK                    __attribute__((weak))
    #define UNUSED                  __attribute__((unused))
    #define DEPRECATED              __attribute__((deprecated))
    #define NO_RETURN               __attribute__((noreturn))
    #define SECTION(x)              __attribute__((section(x)))
#else
    #define ALIGNED(x)
    #define PACKED
    #define ALWAYS_INLINE           inline
    #define NO_INLINE
    #define WEAK
    #define UNUSED
    #define DEPRECATED
    #define NO_RETURN
    #define SECTION(x)
#endif

/* IRAM attributes */
#define IRAM_ATTR
#define DRAM_ATTR
#define RTC_ATTR
#define CACHE_ALIGNED ALIGNED(32)

#ifdef __cplusplus
}
#endif

#endif /* ESP_ATTR_H */
