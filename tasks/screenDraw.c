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
	printTitles();

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

		//empty queue for button debouncing
		xQueueReceive(xScreenStateQueue, &isStateChange, xTicksToWait);
		xQueueReceive(xScreenStateQueue, &isStateChange, xTicksToWait);

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


	float frequency = 22;
	float period = 0.02;
	float amplitude = 0.8;
	float dutyCycle = 24.5;

	if(state){
		//square wave/adc1: frequency, period, duty cycle
		RIT128x96x4StringDraw("ADC1: square wave", 10, 25, 'm');
		printDutyCycle(dutyCycle);
	}
	else{
		//sine wave/adc0: frequency, period, amplitude
		RIT128x96x4StringDraw("ADC0: sine wave  ", 10, 25, 'm');
		printAmplitude(amplitude);
	}

	//printFrequency(frequency);
	//printPeriod(period);
	printADC(state, adcVal);

}

void printADC(int state, unsigned long adcVal){
	char adcMessage [25];
	snprintf (adcMessage, sizeof(adcMessage), "ADC%d val:", state);

	//IntMasterDisable();
	RIT128x96x4StringDraw(adcMessage, 0, 50, 'm');
	//IntMasterEnable();
	snprintf (adcMessage, sizeof(adcMessage), "%lu", adcVal);

	//IntMasterDisable();
	RIT128x96x4StringDraw(adcMessage, 75, 50, 'm');
}

void printFrequency(float frequency){
	char message [8];

	snprintf (message, sizeof(message), "%.2fkHz", frequency);
	//IntMasterDisable();
	RIT128x96x4StringDraw(message, 75, 60, 'm');
	//IntMasterEnable();
}

void printPeriod(float period){
	char message [8];

	snprintf (message, sizeof(message), "%.2fms", period);
	//IntMasterDisable();
	RIT128x96x4StringDraw(message, 75, 70, 'm');
	//IntMasterEnable();
}
void printAmplitude(float amplitude){

	//IntMasterDisable();
	RIT128x96x4StringDraw("Amplitude: ", 0, 80, 'm');
	//IntMasterEnable();
	//char message [8];

	//snprintf (message, sizeof(message), "%.2fV", amplitude);
	//RIT128x96x4StringDraw(message, 75, 80, 'm');
}

void printDutyCycle(float dutyCycle){

	//IntMasterDisable();
	RIT128x96x4StringDraw("Duty Cycle:", 0, 80, 'm');

	//char message [8];

	//snprintf (message, sizeof(message), "%.2f%  ", dutyCycle);
	//RIT128x96x4StringDraw(message, 75, 80, 'm');
	//IntMasterEnable();
}

void printTitles(float period){
	RIT128x96x4StringDraw("Signal to Human", 20, 0, 'm');
	RIT128x96x4StringDraw("Translation Interface", 0, 10, 'm');
	RIT128x96x4StringDraw("Frequency:", 0, 60, 'm');
	RIT128x96x4StringDraw("Period:", 0, 70, 'm');
}
