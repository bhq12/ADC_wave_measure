#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "projectTasks.h"
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
	unsigned long long weightedMovingAverage = 0;
	xSamplesQueue = xQueueCreate(1000, sizeof (unsigned long));

	float samplingPeriod = 0.1; //0.1s or 100ms
	while(1){

		xQueueReceive(xADCQueue, &adcVal, 100);
		xQueueSend(xSamplesQueue, &adcVal, 10);
		samples++;

		if(adcVal > 512){
			dutyOfSample = 100;
		}
		else{
			dutyOfSample = 0;
		}
		xQueueReceive(xADCQueue, &pastSample, 100);
		//weighted moving average, see https://en.wikipedia.org/wiki/Moving_average#Weighted_moving_average
		denominator += samples;
		numerator = numerator + samples * adcVal - total;

		total = total + adcVal - pastSample;
		weightedMovingAverage = numerator / denominator;



		//frequency = count * samplingPeriod;
		xQueueSend(xFrequencyQueue0, &frequency, 10);
	}
}

