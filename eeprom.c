#include "eeprom.h"

//—————————————-

// чтение
/*int32_t EEPROM_int_read(unsigned int addr) 
{    
	int32_t v = 0;
	int8_t vv = 0;
	unsigned int i = addr;
	unsigned int ii = 0;
	for( i; i < (addr + 3); i++ )
	{
		vv = eeprom_read_byte(i);
		ii = i;
		v += vv * (10 ^ ii);
		ii += (2 + i);
	}
	return v;
}

// запись
void EEPROM_int_write(int addr, unsigned int num) {
	int8_t v2 = 0;
	int32_t vv2 = num;
	int32_t vvv2 = 0;
	unsigned int l2 = addr;
	unsigned int ll2 = 6;
	for( l2; l2 < (l2 + 3); l2++ )
	{
		vvv2 = (vv2 % (10 ^ ll2));
		ll2 -= 2;
		v2 = vvv2 / (10 ^ ll2);
		eeprom_write_byte(l2, v2);
	}
}
*/