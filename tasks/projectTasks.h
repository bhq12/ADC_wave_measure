#ifndef __RTOS_TASKS_H__
#define __RTOS_TASKS_H__

#include "FreeRTOS.h"
#include "queue.h"

extern xQueueHandle xADCQueue0;
extern xQueueHandle xADCQueue1;
extern xQueueHandle xScreenStateQueue;

//tasks in use
extern void screenDrawTask();
extern void pollADCTask();

//rubbish testing tasks
extern void queueTestTask( void *pvParameters );
extern void makeNoiseTask( unsigned long *pvParameters );

#endif
