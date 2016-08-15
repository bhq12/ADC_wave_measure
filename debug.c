#include <stdlib.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "driverlib/gpio.h"


//module to allow toggling of pins to allow program debugging and analysis using an oscilliscope
//debugging is on pin PB7
int pinOn;

void initialiseDebugging(){
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0xFF);
	pinOn = 1;

}

void debugPinOn(){
	pinOn = 1;
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0xFF);
}

void debugPinOff(){
	pinOn = 0;
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x00);
}

//TODO: doesn't appear to set pin low, 0x00 wrong value?
void switchDebugPin(){
	if(pinOn == 1){
		pinOn = 0;
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x00);
		int i;
	}
	else if (pinOn == 0){
		pinOn = 1;
		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0xFF);
	}
}
