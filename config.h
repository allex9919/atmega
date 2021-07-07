#ifndef CONFIG_H_
#define CONFIG_H_
 
#include "main.h" 
 
#define ONE_WIRE_PORT      PORTB
#define ONE_WIRE_DDR       DDRB
#define ONE_WIRE_PIN       PINB

//—————————————-

void explodeDoubleNumber(int* numbers, double flt);

//char printTemp(double d);

double getTemp(void);

//—————————————-

#endif /* CONFIG_H_ */