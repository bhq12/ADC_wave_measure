#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "projectTasks.h"
#include "debug.h"
#include "semphr.h"
#include "calculationPacket.h"
#define ADC_FREQUENCY 125000
extern xSemaphoreHandle currentlySampling;
extern int canQueue;
xQueueHandle xADCQueue;
xQueueHandle xScreenQueue;

extern unsigned long adcBuffer [10000];
extern int adcBufferIndex;




xQueueHandle xSamplesQueue;

void calculateFrequencyTask()
{
	unsigned long adcVal;
	unsigned long period;//microseconds
	unsigned long frequency = 0;//hz
	unsigned long averagePeriod = 0;
	unsigned long  samples = 0;
	unsigned long crossing = 0;
	int isHigh;
	int wasHigh;
	unsigned long amplitude;
	unsigned long long lastCrossing = 0;
	int frequencyCount = 0;
	int highSamples = 0;
	unsigned long dutyCycle;

	unsigned long max = 512;
	unsigned long min = 512;
	unsigned long average = 512;

	while(1){
		if(!canQueue){

			while(adcBufferIndex > 0){
				debugPinOn(GPIO_PIN_4);
				adcVal = adcBuffer[adcBufferIndex];
				samples++;

				if(adcVal > max && !(adcVal > 1024)){
					max = adcVal;
				}
				if(adcVal < min){
					min = adcVal;
				}

				if(adcVal > average){
					isHigh = true;
					highSamples++;
				}
				else{
					isHigh = false;
				}

				if(wasHigh && !isHigh){
					//high to low transition
					lastCrossing = crossing;
					crossing = samples;
					if(frequencyCount != 0){
						//frequency += ADC_FREQUENCY / (crossing - lastCrossing);
						averagePeriod += (crossing - lastCrossing);

					}
					frequencyCount++;


				}

				wasHigh = isHigh;
				adcBufferIndex--;
				average = (max + min) / 2;


			}
			dutyCycle = 100 * highSamples / samples;
			averagePeriod = averagePeriod / (frequencyCount - 1);
			//frequency = frequency / frequencyCount;
			frequency = ADC_FREQUENCY / averagePeriod;
			period = 1000000 / frequency; //microseconds
			amplitude = (max - min) * 3000 / 1024;
			Calculation calc;
			calc.frequency = frequency;
			calc.period = period;
			calc.amplitude = amplitude;
			calc.dutyCycle = dutyCycle;
			xQueueSend(xScreenQueue, &calc, 100);
			frequency = 0;
			frequencyCount = 0;
			canQueue = 1;
			samples = 0;
			highSamples = 0;
			max = 0;
			min = 1024;
			debugPinOff(GPIO_PIN_4);
		}


	}
}

