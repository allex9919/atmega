#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"

#define ONE_WIRE_PORT      PORTB
#define ONE_WIRE_DDR       DDRB
#define ONE_WIRE_PIN       PINB

void explodeDoubleNumber(int* numbers, double flt);
double getTemp(uint64_t ds18b20s);

#endif /* CONFIG_H_ */