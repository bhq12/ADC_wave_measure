#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
extern xQueueHandle xTimerQueue0;
extern xQueueHandle xFrequencyQueue0;

void calculateFrequencyTask( )
{
	unsigned long timer;
	unsigned long count;
	float frequency;
	float samplingPeriod = 0.1; //0.1s or 100ms
	while(1){
		xQueueReceive(xTimerQueue0, &timer, 100);
		count = 10000 - timer;
		frequency = count * samplingPeriod;
		xQueueSend(xFrequencyQueue0, &frequency, 10);
	}
}

