#include <stdint.h>

#include "inc/lm3s1968.h"
#include "drivers/rit128x96x4.h"
#include "drivers/class-d.c"
#include "audio/pcm.h"
#include "audio/adpcm.h"
#include "driverlib/adc.h"
#include "FreeRTOS.h"
#include "queue.h"
extern xQueueHandle xADCQueue;


void screenDrawTask( )
{
	RIT128x96x4Init(1000000);
	volatile unsigned long ul;
	portBASE_TYPE xStatus;
	const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	unsigned long adcVal = 0ul;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		xStatus = xQueueReceive(xADCQueue, &adcVal, xTicksToWait);
		//*adcVal++;
		char adcsample [100];



		int n=sprintf (adcsample, "this is a test%lu                     ", adcVal);
//		if((int*)isHigh){
			RIT128x96x4StringDraw(adcsample, 10, 10, 'm');
//			RIT128x96x4StringDraw("                         ", 10, 50, 'm');
//		}
//		else{
//			RIT128x96x4StringDraw("low", 10, 50, 'm');
//			RIT128x96x4StringDraw("                         ", 10, 10, 'm');
//		}




		/* Delay for a period. */
		//for( ul = 0; ul < 0xfffff; ul++ )
		//{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		//}


//		if(xADCQueue){
//			unsigned long adc_reading = 0;
//			ADCIntClear(ADC0_BASE, 0);
			//ADCSequenceDataGet(ADC0_BASE, 0, &adcVal);
//			xQueueSend(xADCQueue,&adc_reading, pdFALSE);
//		}


		//RIT128x96x4StringDraw("                  ", 10, 10, 'm');
	}
}

void makeNoiseTask( void *pvParameters )
{

	ClassDInit((unsigned long)SysCtlClockGet());
	unsigned char pucBuffer[256];
	int i;
	for(i = 0; i < 256; i++){
		pucBuffer[i] = (char)i;
	}

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */


	int test;
	/* As per most tasks, this task is implemented in an infinite loop. */
	volatile unsigned long ul;
	for( ;; )
	{
		test = 3;
		if(!ClassDBusy()){
			ClassDPlayPCM(g_pucPCMData, sizeof(g_pucPCMData));
		}



//		/* Delay for a period. */
		for(ul = 0; ul < 42949; ul++)
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}

	}
}

//*****************************************************************************
//
//  Function to initialise the ADC and associated pins/peripherals
//
//*****************************************************************************
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
	sample[0] = 108ul;
	while(true){

		//Triggers an ADC sampling, using sequence number 2
		ADCProcessorTrigger(ADC0_BASE, 2);

		//Wait for the sampling to finish
		while (!ADCIntStatus(ADC0_BASE, 2, false)) {
		}

		//Obtain the sample
		ADCSequenceDataGet(ADC0_BASE, 2, sample);
		unsigned long value = (unsigned long)sample[0];
		xQueueSend(xADCQueue, &value, 10);
	}
}


void queueTestTask( unsigned long *adcVal){
	unsigned long i = 0ul;
	while(1){
		if(xADCQueue){

			xQueueSend(xADCQueue, &i, 10);
			if(i < 100){
				i++;
			}
			else{
				i = 0ul;
			}

			//int j;
			//for(j = 0; j < 0xffffff; j++){}
		}
	}

}
