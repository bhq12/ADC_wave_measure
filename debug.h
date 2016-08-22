#include "driverlib/gpio.h"
#ifndef DEBUG_H
#define DEBUG_H

extern void initialiseDebugging();

extern void debugPinOn(unsigned char pin);

extern void debugPinOff(unsigned char pin);

extern void debugPinPulse(unsigned char pin);


#endif

