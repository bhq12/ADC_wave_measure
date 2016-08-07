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
static unsigned long sample[1];

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

void pollADCTask(){

	sample[0] = 0ul;
	while(true){

		ADCProcessorTrigger(ADC0_BASE, 3);

		while(!ADCIntStatus(ADC0_BASE, 3, false))
		{
		}
		ADCSequenceDataGet(ADC0_BASE, 0, sample);
		unsigned long value = sample[0];
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
