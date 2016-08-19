#include "semphr.h"
#ifndef ADC_PERIPH_H
#define ADC_PERIPH_H

extern int canQueue;
extern xSemaphoreHandle sampling;
extern unsigned long adcBuffer [4000];
extern int adcBufferIndex;

extern void initADC();

#endif
