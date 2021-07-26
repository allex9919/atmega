#ifndef MAIN_H_

#define MAIN_H_

#undef F_CPU

#define F_CPU 8000000UL

#include <avr/io.h>

#include <avr/interrupt.h>

#include <util/delay.h>

#include <avr/eeprom.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>

#include "lcd.h"

#include "button.h"

#include "config.h"

#include "OneWire.h"

//—————————————

#endif /* MAIN_H_ */