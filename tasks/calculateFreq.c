#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "projectTasks.h"
#include "semphr.h"
#define ADC_FREQUENCY 125000
extern xSemaphoreHandle currentlySampling;
extern int canQueue;
xQueueHandle xADCQueue;
xQueueHandle xFrequencyQueue;

extern unsigned long adcBuffer [10000];
extern int adcBufferIndex;



xQueueHandle xSamplesQueue;

void calculateFrequencyTask()
{
	unsigned long adcVal;
	unsigned long pastSample;
	int dutyCycle = 0;
	unsigned long frequency = 0;
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
	xSamplesQueue = xQueueCreate(10, sizeof (unsigned long));
	int frequencyCount = 0;

	while(1){
		if(!canQueue){

			while(adcBufferIndex > 0){

				//xQueueReceive(xADCQueue, &adcVal, 0);
				adcVal = adcBuffer[adcBufferIndex];

				samples++;



				if(adcVal > 512){
					isHigh = true;
				}
				else{
					isHigh = false;
				}

				if(wasHigh && !isHigh){
					//high to low transition
					lastCrossing = crossing;
					crossing = samples;
					frequency += ADC_FREQUENCY / (crossing - lastCrossing);
					frequencyCount++;
				}





				//frequency = count * samplingPeriod;

				wasHigh = isHigh;
				//xSemaphoreGive(currentlySampling);
				adcBufferIndex--;


			}
			frequency = frequency / frequencyCount;
			xQueueSend(xFrequencyQueue, &frequency, 0);
			frequency = 0;
			frequencyCount = 0;
			canQueue = 1;
			//xSemaphoreTake(currentlySampling, 10);

		}


	}
}

