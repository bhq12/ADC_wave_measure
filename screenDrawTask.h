#ifndef __RTOS_TASKS_H__
#define __RTOS_TASKS_H__

#include "FreeRTOS.h"
#include "queue.h"
extern void makeNoiseTask( unsigned long *pvParameters );
extern void screenDrawTask( void *pvParameters );
extern void pollADCTask( unsigned long *pvParameters );
extern xQueueHandle xADCQueue0;
extern xQueueHandle xADCQueue1;
extern xQueueHandle xScreenStateQueue;
extern void pollADCTask( unsigned long *adcVal);
extern void queueTestTask( void *pvParameters );

#endif
