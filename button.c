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
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода

	unsigned char key_value = 0;
	unsigned char i;
	unsigned char err = 0;
	unsigned char utr = 0;

	while (utr < 1)
	{
		for (i = 0; i < 4; i++)
		{
			PORTD = 0xf0; // Устанавливаем лог. 1 в порт ввода
			_delay_us(10);
			
			PORTD = key_tab[i]; // выводим лог. 0 в порт вывода
			_delay_us(10);

			if ((PIND & 0xf0) == 0b11100000)
			{
				key_value = 1 + i * 3;
				if (key_value == err)
				{
					continue;
				}
				break;
			}
			else if ((PIND & 0xf0) == 0b11010000)
			{
				key_value = 2 + i * 3;
				if (key_value == err)
				{
					continue;
				}
				break;
			}
			else if ((PIND & 0xf0) == 0b10110000)
			{
				key_value = 3 + i * 3;
				if (key_value == err)
				{
					continue;
				}
				break;
			}
		}

		for (i = 0; i < 200; i++)
		{
			PORTD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
			_delay_us(10);
			
			if ((PIND&_BV(i)) == 1)
			{
				if (i > 5)
				{
					return key_value;
				}
				if (i > 100)
				{
					utr--;
					key_value = err;
				}
			}
			
			_delay_ms(1);
		}
		
		utr++;
	}		
}


/*unsigned char key_code[4][4]={{1,2,3,'A'},
                              {4,5,6,'B'},
							  {7,8,9,'C'},
							  {10,11,12,'D'}}; //матрица соответствия кодов клавиш

// Функция опроса клавиатуры
unsigned char scan_key(void)
{
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
	PORTD = 0xF0; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);

	/*DDRD=0x00;	//конфигурируем порт C как вход
	PORTD=0x0F;   //выводим на 4 младших бита порта C лог. 1
	DDRD=0x0F;	//конфигурируем порт B как выход
	PORTD=0x00;   //обнуляем порт B

	_delay_us(10);	//Задержка для устранения всяких переходных процессов, важно ее не забыть!
	
	int i=4;
	if ((PIND&0x10)==0x00) i=0;		//Если нажата клавиша в 0й колонке, i=0
	if ((PIND&0x20)==0x00) i=1;		//Если нажата клавиша в 1й колонке, i=1
	if ((PIND&0x40)==0x00) i=2;           //...
	if ((PIND&0x80)==0x00) i=3;           //Если нажата клавиша в 3й колонке, i=3

	DDRD |= (1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт вывода
	DDRD &= ~(1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт ввода
	PORTD = 0x0F; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);

	/*DDRC =0x0F;	//конфигурируем порт C как выход
	PORTC=0x00;   //обнуляем порт C
	DDRB =0x00;	//конфигурируем порт B как вход
	PORTB=0x0F;   //выводим на 4 младших бита порта B лог. 1

	_delay_us(10);	//Задержка для устранения всяких переходных процессов, важно ее не забыть!
	
	int j=4;
	if ((PIND&0x01)==0x00) j=0;		//Если нажата клавиша в 0й строке, j=0
	if ((PIND&0x02)==0x00) j=1;		//...
	if ((PIND&0x04)==0x00) j=2;
	if ((PIND&0x08)==0x00) j=3;

	if ((i!=4)&&(j!=4)) 
	{			
		//Если была нажата клавиша
		while ((PINB&_BV(j))==0x00);	//Ждем пока кнопку отпустят
		return key_code[i][j];	//Пишем ее код на ЖКИ
	} 
	
}*/