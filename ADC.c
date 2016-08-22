#include "include/FreeRTOS.h"
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "state.h"
#include "debug.h"
#include "semphr.h"


int canQueue = 1;
xSemaphoreHandle sampling;
unsigned long adcBuffer [4000];
int adcBufferIndex;

void restartADCSampling(){
	canQueue = 1;
}

int isCurrentlySampling(){
	return canQueue;
}

static void
ADCIntHandler(void){

	ADCIntClear(ADC_BASE, 2);

	if(adcBufferIndex > 3999){
		canQueue = 0;
		xSemaphoreGiveFromISR(sampling, pdFALSE);
	}

	unsigned long sample[4] = {0};

	ADCSequenceDataGet(ADC_BASE, 2, sample);

	if(canQueue){
		debugPinOn(GPIO_PIN_5);
		if(getState()){
			adcBuffer[adcBufferIndex] = sample[1];
		}
		else{
			adcBuffer[adcBufferIndex] = sample[0];
		}
		adcBufferIndex++;
		debugPinOff(GPIO_PIN_5);
	}
}

void initADC() {

	canQueue = 1;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC);

	SysCtlADCSpeedSet(SYSCTL_ADCSPEED_250KSPS);

    ADCSequenceDisable(ADC_BASE, 2);

	ADCSequenceConfigure(ADC_BASE, 2, ADC_TRIGGER_ALWAYS, 0);

	ADCSequenceStepConfigure(ADC_BASE, 2, 0, ADC_CTL_CH0);

	ADCSequenceStepConfigure(ADC_BASE, 2, 1, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);

	ADCSequenceEnable(ADC_BASE, 2);

	ADCIntRegister(ADC_BASE, 2, ADCIntHandler);

	ADCIntEnable(ADC_BASE, 2);

	ADCIntClear(ADC_BASE, 2);
}
