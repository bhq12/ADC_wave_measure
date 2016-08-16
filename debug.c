#include <stdlib.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


//module to allow toggling of pins to allow program debugging and analysis using an oscilliscope
//debugging is on pin PB7
int pinOn;

void initialiseDebugging(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
	//GPIOPinTypeGPIOOutput(GPIO_PORTH_BASE, GPIO_PIN_2);
	GPIODirModeSet (GPIO_PORTH_BASE, GPIO_PIN_2, GPIO_DIR_MODE_OUT);
	debugPinOff();

}

void debugPinOn(){
	pinOn = 1;
	GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2, 0xFF);
}

void debugPinOff(){
	pinOn = 0;
	GPIOPinWrite(GPIO_PORTH_BASE, GPIO_PIN_2, 0);
}

void debugPinPulse(){

	debugPinOn();
	debugPinOff();
}

void switchDebugPin(){
	if(pinOn == 1){
		debugPinOff();
	}
	else if (pinOn == 0){
		debugPinOn();
	}
}
