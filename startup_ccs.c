//*****************************************************************************
//
// startup_ccs.c - Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************
#include <stdint.h>
/* Stellaris library includes. */
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "tasks/projectTasks.h"
#include "hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "portable/portmacro.h"
#include "driverlib/timer.h"
#include "state.h"
//#include "debug.h"
#include <stdio.h>
/* Demo includes. */
#include "demo_code\basic_io.h"
#define BUTTON_PINS GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
#define TIMER_TIMA_TIMEOUT 0x00000001
//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);
static void ButtonHandler(void);
static void TimerADCHandler(void);
static void TimerFrequencyHandler(void);

extern xQueueHandle xADCQueue;
extern xQueueHandle xFrequencyQueue;
//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern unsigned long __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
void ResetISR(void);
extern void xPortPendSVHandler(void);
extern void vPortSVCHandler(void);
extern void xPortSysTickHandler(void);

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************

#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    IntDefaultHandler,                      // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    vPortSVCHandler,                        // SVCall handler
    IntDefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    xPortPendSVHandler,                     // The PendSV handler
    xPortSysTickHandler,                    // The SysTick handler
    IntDefaultHandler,                      // GPIO Port A
    IntDefaultHandler,                      // GPIO Port B
    IntDefaultHandler,                      // GPIO Port C
    IntDefaultHandler,                      // GPIO Port D
    IntDefaultHandler,                      // GPIO Port E
    IntDefaultHandler,                      // UART0 Rx and Tx
    IntDefaultHandler,                      // UART1 Rx and Tx
    IntDefaultHandler,                      // SSI0 Rx and Tx
    IntDefaultHandler,                      // I2C0 Master and Slave
    IntDefaultHandler,                      // PWM Fault
    IntDefaultHandler,                      // PWM Generator 0
    IntDefaultHandler,                      // PWM Generator 1
    IntDefaultHandler,                      // PWM Generator 2
    IntDefaultHandler,                      // Quadrature Encoder 0
    IntDefaultHandler,                      // ADC Sequence 0
    IntDefaultHandler,                      // ADC Sequence 1
    IntDefaultHandler,                      // ADC Sequence 2
    IntDefaultHandler,                      // ADC Sequence 3
    IntDefaultHandler,                      // Watchdog timer
    TimerFrequencyHandler,                      	// Timer 0 subtimer A
    IntDefaultHandler,                      // Timer 0 subtimer B
    IntDefaultHandler,                      	// Timer 1 subtimer A
	IntDefaultHandler,                      // Timer 1 subtimer B
	TimerADCHandler,                      // Timer 2 subtimer A
    IntDefaultHandler,                      // Timer 2 subtimer B
    IntDefaultHandler,                      // Analog Comparator 0
    IntDefaultHandler,                      // Analog Comparator 1
    IntDefaultHandler,                      // Analog Comparator 2
    IntDefaultHandler,                      // System Control (PLL, OSC, BO)
    IntDefaultHandler,                      // FLASH Control
    IntDefaultHandler,                      // GPIO Port F
	ButtonHandler,                      // GPIO Port G
    IntDefaultHandler,                      // GPIO Port H
    IntDefaultHandler,                      // UART2 Rx and Tx
    IntDefaultHandler,                      // SSI1 Rx and Tx
    IntDefaultHandler,                      // Timer 3 subtimer A
    IntDefaultHandler,                      // Timer 3 subtimer B
    IntDefaultHandler,                      // I2C1 Master and Slave
    IntDefaultHandler,                      // Quadrature Encoder 1
    IntDefaultHandler,                      // CAN0
    IntDefaultHandler,                      // CAN1
    IntDefaultHandler,                      // CAN2
    0,                                      // Reserved
    IntDefaultHandler                       // Hibernate
};


//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

int buttonReset;
static void
ButtonHandler(void)
{
	unsigned long time = TimerValueGet(TIMER0_BASE,TIMER_A);

	GPIOPinIntClear (GPIO_PORTG_BASE, BUTTON_PINS);
	int three = GPIOPinRead (GPIO_PORTG_BASE, GPIO_PIN_3);
	int four = GPIOPinRead (GPIO_PORTG_BASE, GPIO_PIN_4);
	int five = GPIOPinRead (GPIO_PORTG_BASE, GPIO_PIN_5);
	int six = GPIOPinRead (GPIO_PORTG_BASE, GPIO_PIN_6);
	int seven = GPIOPinRead (GPIO_PORTG_BASE, GPIO_PIN_7);

	//if( (!three || !four || !five || !six || !seven) && buttonReset){
		changeState();
		//buttonReset = 0;
		//xQueueSendFromISR(xScreenStateQueue, 1, pdFALSE);
	//}

}

//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
static void
TimerADCHandler(void)
{
//	//debugPinPulse();
//	// Clear the timer interrupt.
//	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
//
//	unsigned long sample[4] = {0};
//
//	//Triggers an ADC sampling, using sequence number 2
//	ADCProcessorTrigger(ADC0_BASE, 2);
//
//	//Wait for the sampling to finish
//	while (!ADCIntStatus(ADC0_BASE, 2, false)) {
//	}
//
//	//Obtain the sample
//	ADCSequenceDataGet(ADC0_BASE, 2, sample);
//
//	if(getState()){
//		xQueueSendFromISR(xADCQueue, &sample[1], pdFALSE);
//	}
//	else{
//		xQueueSendFromISR(xADCQueue, &sample[0], pdFALSE);
//	}
//	TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()/10000);//timer expires 10,000 times per second

	//trigger ADC sampling for next interrupt so no wait loop needed
	//ADCProcessorTrigger(ADC0_BASE, 2);

}

static void
ADCIntHandler(void){

// Clear the timer interrupt.
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	unsigned long sample[4] = {0};
//
//	//Triggers an ADC sampling, using sequence number 2
	ADCProcessorTrigger(ADC0_BASE, 2);
//
//	//Wait for the sampling to finish
	while (!ADCIntStatus(ADC0_BASE, 2, false)) {
	}
//
//	//Obtain the sample
	ADCSequenceDataGet(ADC0_BASE, 2, sample);
//
	if(getState()){
		xQueueSendFromISR(xADCQueue, &sample[1], pdFALSE);
	}
	else{
		xQueueSendFromISR(xADCQueue, &sample[0], pdFALSE);
	}
	TimerLoadSet(TIMER2_BASE, TIMER_A, SysCtlClockGet()/10000);//timer expires 10,000 times per second

	//trigger ADC sampling for next interrupt so no wait loop needed
	ADCProcessorTrigger(ADC0_BASE, 2);
}


static void
TimerFrequencyHandler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	buttonReset = 1;
	//
	// Get the counter value
	//
	//unsigned long timer=TimerValueGet(TIMER1_BASE,TIMER_A);
	//unsigned long frequency = (100000 - timer) * 10;//in Hz  // / 100; // measured in kHz
	//xQueueSendFromISR(xFrequencyQueue, &frequency, pdFALSE);
	//
	// Reset the counter value to 10000
	//
	TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/2);
	TimerLoadSet(TIMER1_BASE, TIMER_A,100000);

}
