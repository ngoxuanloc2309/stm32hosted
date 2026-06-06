#include "cmsis_os_compat.h"

osThreadId_t _osThreadCreate(const _osThreadDef_t *def, void *arg)
{
    osThreadAttr_t attr = {
        .name       = def->name,
        .priority   = def->priority,
        .stack_size = def->stack_size,
    };
    return osThreadNew((osThreadFunc_t)def->func, arg, &attr);
}