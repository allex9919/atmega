#include "button.h"

//—————————————

// Массив значений для порта вывода
unsigned char key_tab[4] = {0b11111110,
                            0b11111101,
							0b11111011,
							0b11110111};

// Функция опроса клавиатуры
unsigned char scan_key(void)
{

	unsigned char key_value = 0;
	unsigned char i = 0;
	
	for (i = 0; i < 4; i++)
	{
		
		PORTD = key_tab[i]; // выводим лог. 0 в порт вывода
		_delay_us(10);

		if ((PIND & 0xf0) == 0b11100000)
		{
			key_value = 1 + i * 3;
		}
		else if ((PIND & 0xf0) == 0b11010000)
		{
			key_value = 2 + i * 3;
		}
		else if ((PIND & 0xf0) == 0b10110000)
		{
			key_value = 3 + i * 3;
		}
	}
	
	return key_value;
}