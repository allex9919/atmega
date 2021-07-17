#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

//#undef F_CPU
//#define F_CPU              8000000UL
#define ONE_WIRE_PORT      PORTB
#define ONE_WIRE_DDR       DDRB
#define ONE_WIRE_PIN       PINB

inline void explodeDoubleNumber(int* numbers, double flt);
char printTemp(double d, uint8_t i);
double getTemp(uint64_t ds18b20s);

#endif /* CONFIG_H_ */