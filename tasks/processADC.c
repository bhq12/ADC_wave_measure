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

void processBuffer();
void calculateWaveProperties(unsigned long max, unsigned long min, unsigned long periods, unsigned long samples, unsigned long frequencyCount, unsigned long highSamples);
void sendCalculation(unsigned long frequency, unsigned long period, unsigned long amplitude, unsigned long dutyCycle);

void processADCDataTask()
{
	while(1){
		xSemaphoreTake(sampling, 100);
		if(!isCurrentlySampling()){
			debugPinOn(GPIO_PIN_4);

			processBuffer();
			restartADCSampling();

			debugPinOff(GPIO_PIN_4);
		}
	}
}

void processBuffer(){
	unsigned long samples = 0;
	unsigned long max = 0;
	unsigned long min = 1024;
	unsigned long average = 512;
	unsigned long highSamples = 0;
	unsigned long crossing = 0;
	unsigned long frequencyCount = 0;
	int isHigh = 0;
	int wasHigh = 0;
	unsigned long periods = 0;

	while(adcBufferIndex > 0){

		unsigned long adcVal = adcBuffer[adcBufferIndex];
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
			//high to low transition has occurred
			unsigned long lastCrossing = crossing;
			crossing = samples;
			if(frequencyCount != 0){
				periods += (crossing - lastCrossing);
			}
			frequencyCount++;
		}

		wasHigh = isHigh;
		adcBufferIndex--;
		average = (max + min) / 2;
	}
	calculateWaveProperties(max, min, periods, samples, frequencyCount, highSamples);
}

void calculateWaveProperties(unsigned long max, unsigned long min, unsigned long periods, unsigned long samples, unsigned long frequencyCount, unsigned long highSamples){
	unsigned long dutyCycle = 100 * highSamples / samples;


	float averagePeriod = (float)periods / (frequencyCount - 1);
	float highAccuracyFrequency = ADC_FREQUENCY / averagePeriod;

	unsigned long frequency = (unsigned long)highAccuracyFrequency;
	unsigned long period = 1000000 / frequency; //microseconds
	unsigned long amplitude = (max - min) * 1500 / 1024;
	sendCalculation(frequency, period, amplitude, dutyCycle);
}

void sendCalculation(unsigned long frequency, unsigned long period, unsigned long amplitude, unsigned long dutyCycle){
	Calculation calc;
	calc.frequency = frequency;
	calc.period = period;
	calc.amplitude = amplitude;
	calc.dutyCycle = dutyCycle;
	xQueueSend(xScreenQueue, &calc, 100);
	xSemaphoreGive(screenQueueCount);
}

