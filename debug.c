#include <stdlib.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
//module to allow output toggling of GPIO pins to allow program profiling and analysis using an oscilliscope
#define DEBUG_PINS GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

void debugPinOn(unsigned char pin){
	GPIOPinWrite(GPIO_PORTB_BASE, pin, 0xFF);
}

void debugPinOff(unsigned char pin){
	GPIOPinWrite(GPIO_PORTB_BASE, pin, 0);
}

void debugPinPulse(unsigned char pin){
	debugPinOn(pin);
	debugPinOff(pin);
}

void initialiseDebugging(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIODirModeSet (GPIO_PORTB_BASE, DEBUG_PINS, GPIO_DIR_MODE_OUT);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, DEBUG_PINS);
	debugPinOff(DEBUG_PINS);
}

