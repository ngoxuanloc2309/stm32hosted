#ifndef __PLATFORM_WRAPPER_H
#define __PLATFORM_WRAPPER_H

#include <stdint.h>
#include <stddef.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"
#include "app_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ==== Type Definitions ==== */
#define thread_handle_t                 TaskHandle_t
#define semaphore_handle_t              SemaphoreHandle_t

/* ==== Constants ==== */
#define MCU_SYS                         1
#define TIMEOUT_PSERIAL_RESP            30

#define CTRL__TIMER_ONESHOT             0
#define CTRL__TIMER_PERIODIC            1

#define HOSTED_SEM_BLOCKING             -1
#define HOSTED_SEM_NON_BLOCKING         0

#define CTRL_PATH_TASK_STACK_SIZE       4096
#define CTRL_PATH_TASK_PRIO             ( tskIDLE_PRIORITY + 4 )

/* ==== Macros ==== */
#define hosted_mem_free(x) \
{ \
    if (x) { \
        hosted_free(x); \
        x = NULL; \
    } \
}

/* ==== Struct Forward Declarations ==== */
struct serial_drv_handle_t;
struct timer_handle_t;

/* ==== Memory ==== */
void *hosted_malloc(size_t size);
void *hosted_calloc(size_t blk_no, size_t size);
void *hosted_realloc(void *mem, size_t newsize);
void  hosted_free(void *ptr);

/* ==== Thread ==== */
void *hosted_thread_create(void (*start_routine)(void const *), void *arg);
int   hosted_thread_cancel(void *thread_handle);

/* ==== Semaphore ==== */
void *hosted_create_semaphore(int init_value);
int   hosted_get_semaphore(void *semaphore_handle, int timeout);
int   hosted_post_semaphore(void *semaphore_handle);
int   hosted_destroy_semaphore(void *semaphore_handle);

/* ==== Timer ==== */
void *hosted_timer_start(int duration, int type,
        void (*timeout_handler)(void const *), void *arg);
int   hosted_timer_stop(void *timer_handle);

/* ==== Sleep ==== */
unsigned int sleep(unsigned int seconds);
unsigned int msleep(unsigned int mseconds);

/* ==== Control Path ==== */
int control_path_platform_init(void);
int control_path_platform_deinit(void);

/* ==== Serial Driver ==== */
struct serial_drv_handle_t *serial_drv_open(const char *transport);
int      serial_drv_write(struct serial_drv_handle_t *serial_drv_handle,
             uint8_t *buf, int in_count, int *out_count);
uint8_t *serial_drv_read(struct serial_drv_handle_t *serial_drv_handle,
             uint32_t *out_nbyte);
int      serial_drv_close(struct serial_drv_handle_t **serial_drv_handle);

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_WRAPPER_H */