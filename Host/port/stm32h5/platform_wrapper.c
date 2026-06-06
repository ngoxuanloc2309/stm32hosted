#include <string.h>
#include <stdio.h>
#include "platform_wrapper.h"
#include "common.h"
#include "serial_ll_if.h"
#include "serial_if.h"
#include "usart.h"

/* ==== Constants ==== */
#define SEC_TO_MILLISEC(x)              ((x) * 1000)

#define HOSTED_CALLOC(buff, nbytes) do {                        \
    buff = (uint8_t *)hosted_calloc(1, nbytes);                 \
    if (!buff) {                                                \
        printf("%s: alloc failed\r\n", __func__);               \
        goto free_bufs;                                         \
    }                                                           \
} while(0)

/* ==== Private Types ==== */
struct serial_drv_handle_t {
    int handle;
};

struct timer_handle_t {
    TimerHandle_t   timer_id;
    void            (*handler)(void const *);
    void            *arg;
};

/* ==== Private Variables ==== */
static SemaphoreHandle_t    read_sem     = NULL;
static serial_ll_handle_t  *serial_ll_if = NULL;

/* ==== Printf Redirect to UART3 ==== */
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&LOG_UART, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/* ==== Memory ==== */
void *hosted_malloc(size_t size)
{
    return pvPortMalloc(size);
}

void *hosted_calloc(size_t blk_no, size_t size)
{
    size_t total = blk_no * size;
    void *ptr = pvPortMalloc(total);
    if (ptr)
        memset(ptr, 0, total);
    return ptr;
}

void *hosted_realloc(void *mem, size_t newsize)
{
    if (newsize == 0) {
        hosted_mem_free(mem);
        return NULL;
    }
    void *p = pvPortMalloc(newsize);
    if (p && mem) {
        memcpy(p, mem, newsize);
        vPortFree(mem);
    }
    return p;
}

void hosted_free(void *ptr)
{
    if (ptr)
        vPortFree(ptr);
}

/* ==== Sleep ==== */
unsigned int msleep(unsigned int mseconds)
{
    vTaskDelay(pdMS_TO_TICKS(mseconds));
    return 0;
}

unsigned int sleep(unsigned int seconds)
{
    vTaskDelay(pdMS_TO_TICKS(SEC_TO_MILLISEC(seconds)));
    return 0;
}

/* ==== Thread ==== */
typedef struct {
    void (*start_routine)(void const *);
    void *arg;
} thread_ctx_t;

static void thread_entry(void *param)
{
    thread_ctx_t *ctx = (thread_ctx_t *)param;
    ctx->start_routine(ctx->arg);
    vPortFree(ctx);
    vTaskDelete(NULL);
}

void *hosted_thread_create(void (*start_routine)(void const *), void *arg)
{
    if (!start_routine) {
        printf("start_routine is NULL\r\n");
        return NULL;
    }

    thread_ctx_t *ctx = (thread_ctx_t *)pvPortMalloc(sizeof(thread_ctx_t));
    if (!ctx) {
        printf("thread ctx alloc failed\r\n");
        return NULL;
    }
    ctx->start_routine = start_routine;
    ctx->arg           = arg;

    TaskHandle_t *handle = (TaskHandle_t *)pvPortMalloc(sizeof(TaskHandle_t));
    if (!handle) {
        vPortFree(ctx);
        return NULL;
    }

    if (xTaskCreate(thread_entry, "hosted_task",
            CTRL_PATH_TASK_STACK_SIZE / sizeof(StackType_t),
            ctx, CTRL_PATH_TASK_PRIO, handle) != pdPASS) {
        printf("task create failed\r\n");
        vPortFree(ctx);
        vPortFree(handle);
        return NULL;
    }
    return (void *)handle;
}

int hosted_thread_cancel(void *thread_handle)
{
    if (!thread_handle)
        return STM_FAIL;
    vTaskDelete(*(TaskHandle_t *)thread_handle);
    vPortFree(thread_handle);
    return STM_OK;
}

/* ==== Semaphore ==== */
void *hosted_create_semaphore(int init_value)
{
    SemaphoreHandle_t *sem = (SemaphoreHandle_t *)pvPortMalloc(sizeof(SemaphoreHandle_t));
    if (!sem)
        return NULL;

    *sem = xSemaphoreCreateCounting(100, (UBaseType_t)init_value);
    if (!*sem) {
        vPortFree(sem);
        return NULL;
    }
    return (void *)sem;
}

int hosted_get_semaphore(void *semaphore_handle, int timeout)
{
    if (!semaphore_handle)
        return STM_FAIL;

    SemaphoreHandle_t sem = *(SemaphoreHandle_t *)semaphore_handle;
    TickType_t ticks;

    if (timeout == HOSTED_SEM_NON_BLOCKING)
        ticks = 0;
    else if (timeout == HOSTED_SEM_BLOCKING)
        ticks = portMAX_DELAY;
    else
        ticks = pdMS_TO_TICKS(SEC_TO_MILLISEC(timeout));

    return (xSemaphoreTake(sem, ticks) == pdTRUE) ? STM_OK : STM_FAIL;
}

int hosted_post_semaphore(void *semaphore_handle)
{
    if (!semaphore_handle)
        return STM_FAIL;

    SemaphoreHandle_t sem = *(SemaphoreHandle_t *)semaphore_handle;
    return (xSemaphoreGive(sem) == pdTRUE) ? STM_OK : STM_FAIL;
}

int hosted_destroy_semaphore(void *semaphore_handle)
{
    if (!semaphore_handle)
        return STM_FAIL;

    SemaphoreHandle_t sem = *(SemaphoreHandle_t *)semaphore_handle;
    vSemaphoreDelete(sem);
    vPortFree(semaphore_handle);
    return STM_OK;
}

/* ==== Timer ==== */
static void timer_callback(TimerHandle_t xTimer)
{
    struct timer_handle_t *ctx = (struct timer_handle_t *)pvTimerGetTimerID(xTimer);
    if (ctx && ctx->handler)
        ctx->handler(ctx->arg);
}

void *hosted_timer_start(int duration, int type,
        void (*timeout_handler)(void const *), void *arg)
{
    struct timer_handle_t *ctx =
        (struct timer_handle_t *)pvPortMalloc(sizeof(struct timer_handle_t));
    if (!ctx) {
        printf("timer alloc failed\r\n");
        return NULL;
    }
    ctx->handler = timeout_handler;
    ctx->arg     = arg;

    UBaseType_t reload = (type == CTRL__TIMER_PERIODIC) ? pdTRUE : pdFALSE;

    ctx->timer_id = xTimerCreate("hosted_tmr",
            pdMS_TO_TICKS(SEC_TO_MILLISEC(duration)),
            reload, (void *)ctx, timer_callback);

    if (!ctx->timer_id) {
        printf("timer create failed\r\n");
        vPortFree(ctx);
        return NULL;
    }

    if (xTimerStart(ctx->timer_id, 0) != pdPASS) {
        printf("timer start failed\r\n");
        xTimerDelete(ctx->timer_id, 0);
        vPortFree(ctx);
        return NULL;
    }
    return (void *)ctx;
}

int hosted_timer_stop(void *timer_handle)
{
    if (!timer_handle)
        return STM_FAIL;

    struct timer_handle_t *ctx = (struct timer_handle_t *)timer_handle;
    xTimerStop(ctx->timer_id, 0);
    xTimerDelete(ctx->timer_id, 0);
    vPortFree(ctx);
    return STM_OK;
}

/* ==== Control Path ==== */
static void control_path_rx_indication(void)
{
    if (read_sem)
        xSemaphoreGive(read_sem);
}

int control_path_platform_init(void)
{
    read_sem = xSemaphoreCreateCounting(100, 0);
    if (!read_sem) {
        printf("read_sem create failed\r\n");
        return STM_FAIL;
    }

    serial_ll_if = serial_ll_init(control_path_rx_indication);
    if (!serial_ll_if) {
        printf("serial_ll_init failed\r\n");
        return STM_FAIL;
    }

    if (STM_OK != serial_ll_if->fops->open(serial_ll_if)) {
        printf("serial_ll open failed\r\n");
        return STM_FAIL;
    }
    return STM_OK;
}

int control_path_platform_deinit(void)
{
    if (!serial_ll_if)
        return STM_FAIL;
    if (STM_OK != serial_ll_if->fops->close(serial_ll_if)) {
        printf("serial_ll close failed\r\n");
        return STM_FAIL;
    }
    return STM_OK;
}

/* ==== Serial Driver ==== */
struct serial_drv_handle_t *serial_drv_open(const char *transport)
{
    if (!transport) {
        printf("serial_drv_open: invalid param\r\n");
        return NULL;
    }

    struct serial_drv_handle_t *handle =
        (struct serial_drv_handle_t *)hosted_calloc(1, sizeof(struct serial_drv_handle_t));
    if (!handle)
        printf("serial_drv_open: alloc failed\r\n");

    return handle;
}

int serial_drv_write(struct serial_drv_handle_t *serial_drv_handle,
        uint8_t *buf, int in_count, int *out_count)
{
    if (!serial_drv_handle || !buf || !in_count || !out_count) {
        printf("serial_drv_write: invalid params\r\n");
        return STM_FAIL;
    }

    if (!serial_ll_if || !serial_ll_if->fops || !serial_ll_if->fops->write) {
        printf("serial_ll not ready\r\n");
        return STM_FAIL;
    }

    int ret = serial_ll_if->fops->write(serial_ll_if, buf, in_count);
    if (ret != STM_OK) {
        *out_count = 0;
        return STM_FAIL;
    }

    *out_count = in_count;
    return STM_OK;
}

uint8_t *serial_drv_read(struct serial_drv_handle_t *serial_drv_handle,
        uint32_t *out_nbyte)
{
    uint16_t init_read_len = 0;
    uint16_t rx_buf_len    = 0;
    uint8_t *read_buf      = NULL;
    uint8_t *buf           = NULL;
    uint32_t buf_len       = 0;
    const char *ep_name    = CTRL_EP_NAME_RESP;

    if (!serial_drv_handle || !out_nbyte) {
        printf("serial_drv_read: invalid params\r\n");
        return NULL;
    }

    *out_nbyte = 0;

    if (!read_sem) {
        printf("read_sem not initialized\r\n");
        return NULL;
    }

    /* block until control_path_rx_indication signals */
    if (xSemaphoreTake(read_sem, portMAX_DELAY) != pdTRUE) {
        printf("read_sem take failed\r\n");
        return NULL;
    }

    if (!serial_ll_if || !serial_ll_if->fops || !serial_ll_if->fops->read) {
        printf("serial_ll not ready for read\r\n");
        return NULL;
    }

    read_buf = serial_ll_if->fops->read(serial_ll_if, &rx_buf_len);
    if (!read_buf || !rx_buf_len) {
        printf("serial_ll read failed\r\n");
        return NULL;
    }

    /* Step 1: read fixed TLV header to get payload length */
    init_read_len = SIZE_OF_TYPE + SIZE_OF_LENGTH + strlen(ep_name) +
                    SIZE_OF_TYPE + SIZE_OF_LENGTH;

    if (rx_buf_len < init_read_len) {
        printf("serial buf too short\r\n");
        goto free_bufs;
    }

    HOSTED_CALLOC(buf, init_read_len);
    memcpy(buf, read_buf, init_read_len);

    if (parse_tlv(buf, &buf_len) || !buf_len) {
        printf("parse_tlv failed\r\n");
        hosted_mem_free(buf);
        goto free_bufs;
    }

    if (rx_buf_len < (init_read_len + buf_len)) {
        printf("buf smaller than expected\r\n");
        hosted_mem_free(buf);
        goto free_bufs;
    }

    hosted_mem_free(buf);

    /* Step 2: read variable payload */
    HOSTED_CALLOC(buf, buf_len);
    memcpy(buf, read_buf + init_read_len, buf_len);
    hosted_mem_free(read_buf);

    *out_nbyte = buf_len;
    return buf;

free_bufs:
    hosted_mem_free(read_buf);
    hosted_mem_free(buf);
    return NULL;
}

int serial_drv_close(struct serial_drv_handle_t **serial_drv_handle)
{
    if (!serial_drv_handle || !(*serial_drv_handle)) {
        printf("serial_drv_close: invalid param\r\n");
        return STM_FAIL;
    }
    hosted_mem_free(*serial_drv_handle);
    *serial_drv_handle = NULL;
    return STM_OK;
}