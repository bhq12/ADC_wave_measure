
#ifndef CALCULATION_PACKET_H
#define CALCULATION_PACKET_H

typedef struct
{
	unsigned long frequency;//hz
	unsigned long period;//microseconds
	unsigned long dutyCycle;//%
	unsigned long amplitude;//mV
} Calculation;

#endif

