#ifndef __RTOS_TASKS_H__
#define __RTOS_TASKS_H__

#include "FreeRTOS.h"
#include "queue.h"

extern xQueueHandle xScreenQueue;

extern void screenDrawTask();
extern void processADCDataTask();

#endif
