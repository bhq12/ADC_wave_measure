
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"

#ifndef __RTOS_TASKS_H__
#define __RTOS_TASKS_H__


extern xQueueHandle xScreenQueue;
extern xSemaphoreHandle screenQueueCount;

extern void screenDrawTask();
extern void processADCDataTask();

#endif
