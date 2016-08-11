#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
extern xQueueHandle xADCQueue0;
extern xQueueHandle xADCQueue1;

void initialiseADC(void){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinTypeADC(GPIO_PORTA_BASE, GPIO_PIN_1); //ADC1
	GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_1); //ADC0

	//Set up ADC0 to use sequence number 2. This means that
	//
	//ADC_TRIGGER_PROCESSOR means that we can cause the processor
	//to trigger an ADC sample, which allows us to later read a sample
	ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);


	//Configure a step of the sample sequencer.
	//In this case, we are configuring ADC0 to use sequence number 2,
	//and we are configuring step 0. Step 0 will use input channel 0
	//ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
	ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH0);

	ADCSequenceStepConfigure(ADC0_BASE, 2, 1, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);
	//Enable sample sequence 2
	ADCSequenceEnable(ADC0_BASE, 2);

	//Clear the source of a sample sequence interrupt
	//This means that the interrupt no longer asserts
	ADCIntClear(ADC0_BASE, 2);
}


void pollADCTask(){

	initialiseADC();
	unsigned long sample[4];
	sample[0] = 0ul;
	sample[1] = 0ul;
	while(true){

		//Triggers an ADC sampling, using sequence number 2
		ADCProcessorTrigger(ADC0_BASE, 2);

		//Wait for the sampling to finish
		while (!ADCIntStatus(ADC0_BASE, 2, false)) {
		}

		//Obtain the sample
		ADCSequenceDataGet(ADC0_BASE, 2, sample);
		unsigned long valueAdc0 = (unsigned long)sample[0];
		unsigned long valueAdc1 = (unsigned long)sample[1];

		xQueueSend(xADCQueue0, &valueAdc0, 10);
		xQueueSend(xADCQueue1, &valueAdc1, 10);
	}
}


