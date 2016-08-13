/*
    FreeRTOS V6.0.5 - Copyright (C) 2009 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "queue.h"
#include "timers.h"

/* Stellaris library includes. */
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"

#include "drivers/class-d.h"
#include "drivers/rit128x96x4.h"
#include "tasks/projectTasks.h"

#include "hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h""
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"


/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )
#define BUTTON_PINS GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

/* The task function. */
void vTaskFunction( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask1 = "Task 1";
const char *pcTextForTask2 = "Task 2";

xQueueHandle xADCQueue0;
xQueueHandle xADCQueue1;
xQueueHandle xScreenStateQueue;


void initADC(void){
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

//*****************************************************************************
//
//  Function to initialise the buttons for reading
//
//*****************************************************************************
void initButtons(void){

    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);

    GPIOPadConfigSet (GPIO_PORTG_BASE, BUTTON_PINS, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet(GPIO_PORTG_BASE, BUTTON_PINS, GPIO_BOTH_EDGES);
    IntPrioritySet(INT_GPIOG, configKERNEL_INTERRUPT_PRIORITY);
    GPIOPinIntEnable(GPIO_PORTG_BASE, BUTTON_PINS);
    IntEnable(INT_GPIOG);
}

//*****************************************************************************
//
//  Function to initialise the timer
//
//*****************************************************************************
void initTimer(void){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);


	//
	// Enable processor interrupts.
	//
	IntMasterEnable();

	//
	// Configure the two 32-bit periodic timers.
	//
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerControlEvent(TIMER0_BASE, TIMER_A, TIMER_EVENT_BOTH_EDGES);
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/1000);//timer expires 1,000 times per second

	//
	// Setup the interrupts for the timer timeouts.
	//
	IntPrioritySet(INT_TIMER0A, configKERNEL_INTERRUPT_PRIORITY);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER0A);
	//
	// Enable the timers.
	//
	TimerEnable(TIMER0_BASE, TIMER_A);
}
/*-----------------------------------------------------------*/

int main( void )
{

	/* Set the clocking to run from the PLL at 50 MHz.  Assumes 8MHz XTAL,
	whereas some older eval boards used 6MHz. */
	SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );
	initButtons();
	initADC();
	initTimer();

	xADCQueue0 = xQueueCreate(10, sizeof (unsigned long));
	xADCQueue1 = xQueueCreate(10, sizeof (unsigned long));
	xScreenStateQueue = xQueueCreate(1, sizeof (int));


	/* Create one of the two tasks. */
	xTaskCreate(	screenDrawTask,			/* Pointer to the function that implements the task. */
					"Task 1",				/* Text name for the task.  This is to facilitate debugging only. */
					240,					/* Stack depth in words. */
					(void*)NULL,	/* Pass the text to be printed in as the task parameter. */
					1,						/* This task will run at priority 1. */
					NULL );					/* We are not using the task handle. */

	/* Create the other task in exactly the same way.  Note this time that we
	are creating the SAME task, but passing in a different parameter.  We are
	creating two instances of a single task implementation. */

	//xTaskCreate( pollADCTask, "Task 2", 240, &adcVal, 1, NULL );
	//xTaskCreate( makeNoiseTask, "Task 3", 240, (void*)NULL, 1, NULL );
	//xTaskCreate( pollADCTask, "Task 3", 240, (void*)NULL, 1, NULL );

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();	
	
	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
}

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}




