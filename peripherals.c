#include "include/FreeRTOS.h"
#include "include/task.h"
#include "queue.h"
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "ADC.h"

#define BUTTON_PINS GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

void initButtons(void){

    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);

    GPIOPadConfigSet (GPIO_PORTG_BASE, BUTTON_PINS, GPIO_STRENGTH_2MA,
           GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet(GPIO_PORTG_BASE, BUTTON_PINS, GPIO_BOTH_EDGES);
    IntPrioritySet(INT_GPIOG, configKERNEL_INTERRUPT_PRIORITY);
    GPIOPinIntEnable(GPIO_PORTG_BASE, BUTTON_PINS);
    IntEnable(INT_GPIOG);
}

void initDebouncingTimer(void){

	// Enable the peripherals used by this example.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	// Enable processor interrupts.
	IntMasterEnable();

	// Configure the two 32-bit periodic timers.
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	// This function configures the timer load value; if the timer is running
	// then the value is immediately loaded into the timer.
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/2);//twice a second

	// Setup the interrupt for the Timer0-TimerA timeouts.
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	// Enable the timers.
	TimerEnable(TIMER0_BASE, TIMER_A);
}

void initPeripherals(){
	initButtons();
	initADC();
	initDebouncingTimer();
}
