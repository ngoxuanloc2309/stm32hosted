
#ifndef __CMSIS_OS_COMPAT_H
#define __CMSIS_OS_COMPAT_H

#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
// #include "lwip/pbuf.h"
#undef mem_free

typedef osSemaphoreId_t     osSemaphoreId;
typedef osMutexId_t         osMutexId;
typedef osThreadId_t        osThreadId;

#define osSemaphoreDef(name)
#define osSemaphore(name)                   NULL
#define osSemaphoreCreate(def, count)       osSemaphoreNew((count), (count), NULL)
#define osSemaphoreWait(sem, timeout)       osSemaphoreAcquire((sem), (timeout))

typedef void (*_os_thread_func_t)(void const *);

typedef struct {
    const char          *name;
    _os_thread_func_t    func;
    osPriority_t         priority;
    uint32_t             stack_size;
} _osThreadDef_t;

#define osThreadDef(tname, tfunc, tprio, tinst, tstack)  \
    static _osThreadDef_t _##tname##_def = {             \
        .name       = #tname,                            \
        .func       = (tfunc),                           \
        .priority   = (osPriority_t)(tprio),             \
        .stack_size = (tstack),                          \
    }

#define osThread(tname)          (&_##tname##_def)
#define osThreadCreate(def, arg) _osThreadCreate((def), (arg))

osThreadId_t _osThreadCreate(const _osThreadDef_t *def, void *arg);

#endif /* __CMSIS_OS_COMPAT_H */
