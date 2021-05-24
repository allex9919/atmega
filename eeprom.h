#ifndef EEPROM_H_

#define EEPROM_H_

#include "main.h"

//void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

//unsigned char EEPROM_read(unsigned int uiAddress);

void EEPROM_write(unsigned int uiAddress, uint32_t ucData);

uint32_t EEPROM_read(unsigned int uiAddress);

#endif /* EEPROM_H_ */