#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

#undef F_CPU
#define F_CPU              8000000UL
#define ONE_WIRE_PORT      PORTB
#define ONE_WIRE_DDR       DDRB
#define ONE_WIRE_PIN       PINB

void explodeDoubleNumber(int* numbers, double flt);
inline void printTemp(double d);
double getTemp(void);

#endif /* CONFIG_H_ */