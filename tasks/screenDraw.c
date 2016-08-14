#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "state.h"
#include "projectTasks.h"


xQueueHandle xADCQueue;
xQueueHandle xFrequencyQueue;

void screenDrawTask( )
{
	RIT128x96x4Init(1000000);
	printTitles();

	//int state = 1;
	unsigned long adcVal;

	for( ;; )
	{
		printStatus(getState(), adcVal);

	}
}

unsigned long receiveFromQueue(xQueueHandle queue){
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	unsigned long val = 0;
	xQueueReceive(queue, &val, xTicksToWait);
	return val;
}

void printStatus(unsigned long adcVal){


	float frequency = 22;
	float period = 0.02;
	float amplitude = 0.8;
	float dutyCycle = 24.5;

	if(getState()){
		//square wave/adc1: frequency, period, duty cycle
		RIT128x96x4StringDraw("ADC1: square wave", 10, 25, 'm');
		printDutyCycle(dutyCycle);
	}
	else{
		//sine wave/adc0: frequency, period, amplitude
		RIT128x96x4StringDraw("ADC0: sine wave  ", 10, 25, 'm');
		printAmplitude(amplitude);
	}

	printFrequency();
	//printPeriod(period);
	printADC();

}

void printADC(){
	unsigned long adcVal = receiveFromQueue(xADCQueue);
	char adcMessage [25];
	snprintf (adcMessage, sizeof(adcMessage), "ADC%d val:", getState());

	//IntMasterDisable();
	RIT128x96x4StringDraw(adcMessage, 0, 50, 'm');
	//IntMasterEnable();
	if(adcVal < 100000){
		snprintf (adcMessage, sizeof(adcMessage), "%lu    ", adcVal);
	}
	else{
		snprintf (adcMessage, sizeof(adcMessage), "%lu", adcVal);
	}


	if(adcVal != 0){
		RIT128x96x4StringDraw(adcMessage, 75, 50, 'm');
	}
	//IntMasterDisable();

}

void printFrequency(){
	unsigned long frequency = receiveFromQueue(xFrequencyQueue);
	char message [8];


	if(frequency < 100000){
		snprintf (message, sizeof(message), "%lu    ", frequency);
	}
	else{
		snprintf (message, sizeof(message), "%lu", frequency);
	}


	if(frequency != 0){
		RIT128x96x4StringDraw(message, 75, 60, 'm');
	}

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
