#include "include/FreeRTOS.h"
#include "include/task.h"
#include "queue.h"
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "drivers/rit128x96x4.h"
#include "hw_ints.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "state.h"
#include "tasks/projectTasks.h"
#include "debug.h"
#include "semphr.h"
#include "calculationPacket.h"
#include "ADC.h"
#include "peripherals.h"


int main( void )
{

	/* Set the clocking to run from the PLL at 50 MHz.  Assumes 8MHz XTAL,
	whereas some older eval boards used 6MHz. */
	SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );
	initialiseDebugging();
	initPeripherals();
	initialiseState();

	adcBufferIndex = 0;
	xScreenQueue = xQueueCreate(10, sizeof (Calculation));
	sampling = xSemaphoreCreateMutex();

	xTaskCreate(screenDrawTask, "Task 1", 240 /*stack depth*/, (void*)NULL, 1, NULL );

	xTaskCreate( processADCDataTask, "Task 3", 240, (void*)NULL, 10, NULL );

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




