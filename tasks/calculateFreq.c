#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "projectTasks.h"
#define ADC_FREQUENCY 10000
xQueueHandle xADCQueue;
xQueueHandle xFrequencyQueue;

xQueueHandle xSamplesQueue;

void calculateFrequencyTask( )
{
	unsigned long adcVal;
	unsigned long pastSample;
	int dutyCycle = 0;
	float frequency;
	unsigned long dutyOfSample = 0;
	unsigned long long samples = 0;
	unsigned long long total = 0;
	unsigned long long numerator = 0;
	unsigned long long denominator = 0;
	unsigned long long averageDuty = 0;
	unsigned long long crossing = 0;
	int isHigh;
	int wasHigh;
	unsigned long long lastCrossing = 0;
	xSamplesQueue = xQueueCreate(100, sizeof (unsigned long));

	while(1){

		xQueueReceive(xADCQueue, &adcVal, 100);
		xQueueSend(xSamplesQueue, &adcVal, 10);
		samples++;

		if(adcVal > 512){
			dutyOfSample = 100;
			isHigh = true;
		}
		else{
			dutyOfSample = 0;
			isHigh = false;
		}


		xQueueReceive(xADCQueue, &pastSample, 100);

		denominator += samples;
		numerator = numerator + samples * adcVal - total;

		total = total + adcVal - pastSample;
		//weighted moving average, see https://en.wikipedia.org/wiki/Moving_average#Weighted_moving_average
		averageDuty = numerator / denominator;

		if(wasHigh && !isHigh){
			//high to low transition
			lastCrossing = crossing;
			crossing = samples;
		}

		frequency = ADC_FREQUENCY / (crossing - lastCrossing);



		//frequency = count * samplingPeriod;
		xQueueSend(xFrequencyQueue, &frequency, 10);
		wasHigh = isHigh;
	}
}

