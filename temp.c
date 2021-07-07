#include "temp.h"

void setup() 
{
	// настраиваем порты
	//DDRB = 0x00;
	PORTB = 0x00;
	//DDRC = 0x00;
	//PORTC = 0x00;
	//DDRD = 0x00;
	//PORTD = 0x00;
	// включаем I2C шину и экран
	I2C_init();
	//LCD_ini();

}

int DHT_read(uint8_t _PIN, temphumi_t* _DATA) 
{

	// обнуляем переменную
	uint8_t DHT_RESPONSE[5] = {0, 0, 0, 0, 0};

	// формируем задержки для старта датчика

	DHT_DDR |= (1 << _PIN);
	DHT_PORT &= ~(1 << _PIN);

	_delay_ms(18);

	DHT_PORT |= (1 << _PIN);
	DHT_DDR &= ~(1 << _PIN);

	_delay_us(40);

	//смотрим, что пришло через 54us и 80us

	if(DHT_PIN & (1 << _PIN)) {
	return 0;
	}

	_delay_us(54);

	if(!DHT_PIN & (1 << _PIN)) {
	return 0;
	}

	_delay_us(80);

	//если датчик готов с нами работать - читаем 5 байт

	uint8_t _bit, _byte;

	while (DHT_PIN & (1 << _PIN));

	for (_byte = 0; _byte < 5; _byte++) {

	DHT_RESPONSE[_byte] = 0;

	for (_bit = 0; _bit < 8; _bit++) {

	while (!(DHT_PIN & (1 << _PIN))); // ждем ....

	_delay_us(30);

	if (DHT_PIN & (1 << _PIN)) { // если пришла 1, записываем ее в нужное место
	DHT_RESPONSE[_byte] |= 1 << (7 - _bit);
	}

	while (DHT_PIN & (1 << _PIN)); // ждем окончания сигнала
	}
	}

	// если пришли все  0 - ошибка приема данных
	if (DHT_RESPONSE[0] + DHT_RESPONSE[1] + DHT_RESPONSE[2] + DHT_RESPONSE[3] == 0) { return 0; }

	// проверяем данные на ликвидность
	if (DHT_RESPONSE[0] + DHT_RESPONSE[1] + DHT_RESPONSE[2] + DHT_RESPONSE[3] != DHT_RESPONSE[4]) { return 0; }

	// если проверка на ликвидность прошла - читаем данные.
	_DATA -> humi = DHT_RESPONSE[0]; // влажность
	_DATA -> temp = DHT_RESPONSE[2];// температура

	return 1;

}