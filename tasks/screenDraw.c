#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
extern xQueueHandle xADCQueue0;
extern xQueueHandle xADCQueue1;
extern xQueueHandle xScreenStateQueue;


void screenDrawTask( )
{
	RIT128x96x4Init(1000000);


	int state = 1;
	unsigned long adcVal;
	xQueueHandle* queue = &xADCQueue1;

	for( ;; )
	{
		state = monitorState(state);
		if(state){
			queue = &xADCQueue1;
		}
		else{
			queue = &xADCQueue0;
		}
		adcVal = receiveFromQueue(*queue);
		printStatus(state, adcVal);
	}
}

int monitorState(int currentState){
	int newState = currentState;
	int isStateChange = 0;

	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	xQueueReceive(xScreenStateQueue, &isStateChange, xTicksToWait);

	if(isStateChange){
		newState = !currentState;
	}

	return newState;
}

unsigned long receiveFromQueue(xQueueHandle queue){
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	unsigned long adcVal = 0;
	xQueueReceive(queue, &adcVal, xTicksToWait);
	return adcVal;
}

void printStatus(int state, unsigned long adcVal){
	char adcMessage [25];
	sprintf (adcMessage, "ADC%d val: %lu   ", state, adcVal);
	RIT128x96x4StringDraw(adcMessage, 10, 10, 'm');
}
