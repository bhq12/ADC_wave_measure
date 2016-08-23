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
#include "ADC.h"

#define ADC_FREQUENCY 125000
xQueueHandle xScreenQueue;
xQueueHandle xSamplesQueue;

void processADCDataTask()
{
	unsigned long adcVal;
	unsigned long period;//microseconds
	unsigned long frequency = 0;//hz
	unsigned long periods = 0;
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
		xSemaphoreTake(sampling, 100);
		/*Calculation calc;

		calc.frequency = 10000;
		calc.period = 100;
		calc.amplitude = 500;
		calc.dutyCycle = 50;

		xQueueSend(xScreenQueue, &calc, 100);
		xSemaphoreGive(screenQueue);*/


		if(!isCurrentlySampling()){

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
						periods += (crossing - lastCrossing);

					}
					frequencyCount++;


				}

				wasHigh = isHigh;
				adcBufferIndex--;
				average = (max + min) / 2;


			}
			dutyCycle = 100 * highSamples / samples;
			//unsigned long periods = periods;
			//periods = periods / (frequencyCount - 1);
			float averagePeriod = (float)periods / (frequencyCount - 1);
			float highAccuracyFrequency = ADC_FREQUENCY / averagePeriod;
			//frequency = frequency / frequencyCount;
			frequency = (unsigned long)highAccuracyFrequency;
			period = 1000000 / frequency; //microseconds
			amplitude = (max - min) * 1500 / 1024;
			Calculation calc;
			calc.frequency = frequency;
			calc.period = period;
			calc.amplitude = amplitude;
			calc.dutyCycle = dutyCycle;
			xQueueSend(xScreenQueue, &calc, 100);
			xSemaphoreGive(screenQueueCount);
			frequency = 0;
			frequencyCount = 0;
			;
			samples = 0;
			highSamples = 0;
			max = 0;
			min = 1024;
			periods = 0;
			restartADCSampling();
			debugPinOff(GPIO_PIN_4);
		}
	}
}
