#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "state.h"
#include "projectTasks.h"
#include "debug.h"
#include "driverlib/gpio.h"
#include "calculationPacket.h"
#include "semphr.h"

xQueueHandle xScreenQueue;
xSemaphoreHandle screenQueueCount;

void screenDrawTask( )
{
	RIT128x96x4Init(1000000);
	printTitles();

	for( ;; )
	{
		xSemaphoreTake(screenQueueCount, 100);
		debugPinOn(GPIO_PIN_6);
		printStatus();
		debugPinOff(GPIO_PIN_6);
	}
}

Calculation receiveFromQueue(xQueueHandle queue){
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	Calculation calc;
	xQueueReceive(queue, &calc, xTicksToWait);
	return calc;
}

void printStatus(){

	if(getState()){
		//square wave/adc1: frequency, period, duty cycle
		RIT128x96x4StringDraw("ADC1: square wave", 10, 25, 'm');
	}
	else{
		//sine wave/adc0: frequency, period, amplitude
		RIT128x96x4StringDraw("ADC0: sine wave  ", 10, 25, 'm');
	}

	Calculation calc = receiveFromQueue(xScreenQueue);
	printCalculation(calc);


}

void printCalculation(Calculation calc){

	char data[15];

	snprintf (data, sizeof(data), "%luHz  ", calc.frequency);
	RIT128x96x4StringDraw(data, 75, 60, 'm');
	memset(data, 0, sizeof data);


	snprintf (data, sizeof(data), "%luus   ", calc.period);
	RIT128x96x4StringDraw(data, 75, 70, 'm');
	memset(data, 0, sizeof data);

	if(getState()){
		RIT128x96x4StringDraw("Duty Cycle:", 0, 80, 'm');
		snprintf (data, sizeof(data), "%lu%%   ", calc.dutyCycle);
		RIT128x96x4StringDraw(data, 75, 80, 'm');
		memset(data, 0, sizeof data);
	}
	else{
		RIT128x96x4StringDraw("Amplitude: ", 0, 80, 'm');
		snprintf (data, sizeof(data), "%lumV ", calc.amplitude);
		RIT128x96x4StringDraw(data, 75, 80, 'm');
		memset(data, 0, sizeof data);
	}
}

void printTitles(float period){
	RIT128x96x4StringDraw("Signal to Human", 20, 0, 'm');
	RIT128x96x4StringDraw("Translation Interface", 0, 10, 'm');
	RIT128x96x4StringDraw("Frequency:", 0, 60, 'm');
	RIT128x96x4StringDraw("Period:", 0, 70, 'm');
}
