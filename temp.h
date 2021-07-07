#ifndef TEMP_H_

#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_PIN PINB

#define DHT_PIN_nomer 3

#include "main.h"

//—————————————-

typedef struct temphumi 
{ 
	// структура данных для DHT11
	uint8_t temp;
	uint8_t humi;
} temphumi_t;

int DHT_read(uint8_t _PIN, temphumi_t* _DATA);// читаем данные с датчика

void setup();

//—————————————-

#endif /* TEMP_H_ */