#include "main.h"

#define DHT_PORT PORTC
#define DHT_DDR DDRC
#define DHT_PIN PINC

#define DHT_PIN_nomer 4

void setup() {
// настраиваем порты
//DDRB = 0x00;
//PORTB = 0x00;
DDRC = 0x00;
PORTC = 0x00;
//DDRD = 0x00;
//PORTD = 0x00;
// включаем I2C шину и экран
I2C_init();
//LCD_ini();

}

typedef struct temphumi { // структура данных для DHT11
uint8_t temp;
uint8_t humi;
} temphumi_t;

int DHT_read(uint8_t _PIN, temphumi_t* _DATA) {

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

//—————————————-

int main (void)
{	
//--------------------------------------------------------------------------
	char buff1[3]; // переменная для хранения данных которые выводим на экран
	char buff2[3]; // переменная для хранения данных которые выводим на экран
	temphumi_t DHT_DATA = {0 ,0}; //переменная для хранения данных которые считываем с датчика
	setup();
//--------------------------------------------------------------------------
	//oneWireInit(PINB2);
	//double temperature;
//--------------------------------------------------------------------------
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
	PORTD = 0xF0; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);
//--------------------------------------------------------------------------	
	DDRB |= (1<<1);    //инициализируем как вход
	//DDRB |= (1<<2);    //инициализируем как вход
	DDRB |= (1<<3);    //инициализируем как вход
	DDRB |= (1<<4);    //инициализируем как вход
	DDRB |= (1<<5);    //инициализируем как вход
	DDRB |= (1<<6);    //инициализируем как вход
//--------------------------------------------------------------------------		
	/*uint32_t mem = 11111;
	uint32_t adr = 0;
	eeprom_busy_wait();
	eeprom_write_dword(adr, mem);*/
//--------------------------------------------------------------------------	
	/*uint32_t mem2 = 22222;
	uint32_t adr2 = 4;
	eeprom_busy_wait();
	eeprom_write_dword(adr2, mem2);*/
//--------------------------------------------------------------------------
	unsigned short m; // объявляем переменную для цикла
	unsigned short i; // объявляем переменную для цикла
	unsigned short ii; // объявляем переменную для цикла
	unsigned short iii; // объявляем переменную для цикла
	unsigned short j; // объявляем переменную для цикла
	short f; 
	short ff; 
	uint32_t n = 0;
	uint8_t nn = 0;
	char Result[6] = ""; 
	char Code[6] = "";
	uint32_t Result_Copy = 0;
	uint32_t Code_Copy = 0;
	uint32_t var = 0;
	uint32_t var2 = 0;
	uint8_t var3 = 0;
	unsigned int c = 0;
	unsigned int cc = 0;
	char Num[4] = "";
	int cycle = 0;
	int cycle2 = 0;
//--------------------------------------------------------------------------	
////////////////////////////////////////////////////////////////////////////		
//--------------------------------------------------------------------------	
	while(1) 
	{	
		if (PINB & (1<<PB5)) 
		{
			while(PINB & (1<<PB5))
			{
				if ((PINB & (1<<PB5)) == 0) 
				{
					break;
				}	
			}	
			for(j=0; j<=66; j++)
			{
				PORTB |=(1<<5);    //высокий уровень 
				_delay_ms(30);
			}
			PORTB &= ~(1<<5);    //низкий уровень
		}
////////////////////////////////////////////////////////////////////////////	
		if (cycle == 0)
		{
			//Включаем порт реле
			PORTB |=(1<<4);    //высокий уровень
			for(j=0; j<=33; j++)
			{
				_delay_ms(30);
			}
			if (cycle2 == 0)
			{
				cycle2 = 1;
////////////////////////////////////////////////////////////////////////////		
				if (DHT_read(DHT_PIN_nomer, &DHT_DATA) == 1) 
				{
					// если данные пришли
					sprintf(buff1, "%d", DHT_DATA.temp);
					//setpos(5, 0);
					//str_lcd(buff);// выводим температуру

					sprintf(buff2, "%d", DHT_DATA.humi);
					//setpos(5, 2);
					//str_lcd(buff);// выводим влажность
				}
				_delay_ms(30);
////////////////////////////////////////////////////////////////////////////				
				lcdInit();
				_delay_ms(10);
				lcdSetCursor(LCD_CURSOR_OFF);
				_delay_ms(10);
				lcdSetDisplay(LCD_DISPLAY_ON);
				_delay_ms(10);
			}
////////////////////////////////////////////////////////////////////////////			
			memset(Result, 0, sizeof Result);//------------------
			f = -1;//------------------
			lcdClear();
			_delay_ms(30);
////////////////////////////////////////////////////////////////////////////		
			for(m=0; m<18000; m++)
			{ 
				if (PINB & (1<<PB5)) 
				{
					while(PINB & (1<<PB5))
					{
						if ((PINB & (1<<PB5)) == 0) 
						{
							break;
						}	
					}	
					lcdClear();
					_delay_ms(30);
					for(j=0; j<=333; j++)
					{
						lcdGotoXY(1,4); 
						lcdPuts("Unlocked"); 
						PORTB |=(1<<5);    //высокий уровень 
						_delay_ms(30);
					}
					PORTB &= ~(1<<5);    //низкий уровень
					lcdClear();
					_delay_ms(30);
				}
////////////////////////////////////////////////////////////////////////////								
				lcdGotoXY(0,3); 
				lcdPuts(buff1);
				lcdGotoXY(0,7); 
				lcdPuts(buff2);
				lcdGotoXY(1,0); 
				lcdPuts("Code:"); 
				Result_Copy = atol(Result);
				lcdGotoXY(1,6); 
				lcdPuts(Result);	
				// Выводим значение нажатой кнопки на индикатор
				for (j=0; j<5; j++)
				{
					if (Result[j]==0)
					{
						if(scan_key()==11) {Result[j]='0'; f++;}
						else if(scan_key()==1) {Result[j]='1'; f++;}
						else if(scan_key()==2) {Result[j]='2'; f++;}
						else if(scan_key()==3) {Result[j]='3'; f++;}
						else if(scan_key()==4) {Result[j]='4'; f++;}
						else if(scan_key()==5) {Result[j]='5'; f++;}
						else if(scan_key()==6) {Result[j]='6'; f++;}
						else if(scan_key()==7) {Result[j]='7'; f++;}
						else if(scan_key()==8) {Result[j]='8'; f++;}
						else if(scan_key()==9) {Result[j]='9'; f++;}
						//_delay_ms(30);
						break;
					}
				}
////////////////////////////////////////////////////////////////////////////			
				if(scan_key()==10)  
				{
					cycle--;
					//_delay_ms(30);
					if(Result[4]!=0) 
					{
						for (n=4; n<129; n+=4)
						{
							eeprom_busy_wait();
							var = eeprom_read_dword(n);
							if  (Result_Copy  ==  var) 
							{ 
								lcdClear();
								_delay_ms(30);
								for(j=0; j<=333; j++)
								{
									lcdGotoXY(1,4); 
									lcdPuts("Unlocked"); 
									//Включаем порт реле
									//PORTB |=(1<<4);    //высокий уровень
									//зеленый светодиод
									PORTB |=(1<<5);    //высокий уровень 
									_delay_ms(30);
								}
								PORTB &= ~(1<<5);    //низкий уровень
								break;
							}
						}
//--------------------------------------------------------------------------				
						n = 0;
						eeprom_busy_wait();
						var = eeprom_read_dword(n);
						if (Result_Copy == var)  
						{
							lcdClear();
							_delay_ms(30);
							for(i=0; i<=2000; i++)
							{
								memset(Code, 0, sizeof Code);//-------------
								c = 0;//----------
								cc = 0;//----------
								ff = -1;//----------
								lcdGotoXY(0,0);
								lcdPuts("*:Add/#:Delete");
								lcdGotoXY(1,0);
								lcdPuts("0:List/1:Change");
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==10) 
								{
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<=6000; ii++)
									{
										lcdGotoXY(0,0);
										lcdPuts("*:Add-");
										Code_Copy = atol(Code);
										lcdGotoXY (0,7);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<5; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {Code[j]='0'; ff++;}
												else if(scan_key()==1) {Code[j]='1'; ff++;}
												else if(scan_key()==2) {Code[j]='2'; ff++;}
												else if(scan_key()==3) {Code[j]='3'; ff++;}
												else if(scan_key()==4) {Code[j]='4'; ff++;}
												else if(scan_key()==5) {Code[j]='5'; ff++;}
												else if(scan_key()==6) {Code[j]='6'; ff++;}
												else if(scan_key()==7) {Code[j]='7'; ff++;}
												else if(scan_key()==8) {Code[j]='8'; ff++;}
												else if(scan_key()==9) {Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==10) 
										{
											//_delay_ms(30);
											if(Code[4]!=0) 
											{
												for(n=4; n<129; n+=4)
												{
													nn = n;
													eeprom_busy_wait();
													var3 = eeprom_read_byte(nn);
													if (var3 == 0xFF)
													{
														eeprom_busy_wait();
														eeprom_write_dword(n, Code_Copy);
														lcdClear();
														_delay_ms(30);
														for(iii=0; iii<=100; iii++)
														{
															lcdGotoXY(1,5);
															lcdPuts("Added");
															//зеленый светодиод
															//PORTB |=(1<<5);    //высокий уровень
															_delay_ms(30);
														}
														//PORTB = 0x00;
														break;
													}
												}
												i = 0;
												break;
											}
											else 
											{
												//memset(Code, 0, sizeof Code);//----------
												lcdClear();
												_delay_ms(30);
												for(iii=0; iii<=100; iii++)
												{
													lcdGotoXY(1,1); 
													lcdPuts("Min. 5 number");
													//красный светодиод
													PORTB |=(1<<6);    //высокий уровень
													_delay_ms(30);
												}
												PORTB &= ~(1<<6);    //низкий уровень
												lcdClear();
												_delay_ms(30);
											}
										}
//--------------------------------------------------------------------------								
										if(scan_key()==12)
										{
											//_delay_ms(30);
											Code[ff] = 0;
											ff--;
											for(iii=0; iii<=1; iii++)
											{
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(30);
											}
											PORTB &= ~(1<<6);    //низкий уровень
											lcdClear();
											_delay_ms(30);
										}
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==12) 
								{
									//_delay_ms(30);
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<=6000; ii++)
									{
										lcdGotoXY(0,0);
										lcdPuts("*:Delete-");
										Code_Copy = atol(Code);
										lcdGotoXY (0,10);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<5; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {Code[j]='0'; ff++;}
												else if(scan_key()==1) {Code[j]='1'; ff++;}
												else if(scan_key()==2) {Code[j]='2'; ff++;}
												else if(scan_key()==3) {Code[j]='3'; ff++;}
												else if(scan_key()==4) {Code[j]='4'; ff++;}
												else if(scan_key()==5) {Code[j]='5'; ff++;}
												else if(scan_key()==6) {Code[j]='6'; ff++;}
												else if(scan_key()==7) {Code[j]='7'; ff++;}
												else if(scan_key()==8) {Code[j]='8'; ff++;}
												else if(scan_key()==9) {Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==10) 
										{
											//_delay_ms(30);
											if(Code[4]!=0) 
											{
												for(n=4; n<129; n+=4)
												{
													eeprom_busy_wait();
													var2 = eeprom_read_dword(n);
													if (Code_Copy == var2)
													{
														nn = n;
														eeprom_busy_wait();
														eeprom_write_byte(nn, 0xFF);
														nn++;
														eeprom_busy_wait();
														eeprom_write_byte(nn, 0xFF);
														nn++;
														eeprom_busy_wait();
														eeprom_write_byte(nn, 0xFF);
														nn++;
														eeprom_busy_wait();
														eeprom_write_byte(nn, 0xFF);
														lcdClear();
														_delay_ms(30);
														for(iii=0; iii<=100; iii++)
														{
															lcdGotoXY(1,4);
															lcdPuts("Deleted");
															//зеленый светодиод
															//PORTB |=(1<<5);    //высокий уровень
															_delay_ms(30);
														}
														//PORTB = 0x00;
														break;
													}
												}
												i = 0;
												break;
											}
											else 
											{
												//memset(Code, 0, sizeof Code);//----------
												lcdClear();
												_delay_ms(30);
												for(iii=0; iii<=100; iii++)
												{
													lcdGotoXY(1,1); 
													lcdPuts("Min. 5 number");
													//красный светодиод
													PORTB |=(1<<6);    //высокий уровень
													_delay_ms(30);
												}
												PORTB &= ~(1<<6);    //низкий уровень
												lcdClear();
												_delay_ms(30);
											}
										}
//--------------------------------------------------------------------------								
										if(scan_key()==12)
										{
											//_delay_ms(30);
											Code[ff] = 0;
											ff--;
											for(iii=0; iii<=1; iii++)
											{
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(30);
											}
											PORTB &= ~(1<<6);    //низкий уровень
											lcdClear();
											_delay_ms(30);
										}
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==11) 
								{
									//_delay_ms(30);
									for(n=4; n<129; n+=4)
									{
										memset(Code, 0, sizeof Code);//-------------
										memset(Num, 0, sizeof Num);//--------------
										nn = n;
										eeprom_busy_wait();
										var3 = eeprom_read_byte(nn);
										if (var3 == 0xFF)
										{
											continue;
										}
										else
										{
											c++;
											var2 = 0;
											if (cc == 0)
											{
												eeprom_busy_wait();
												var2 = eeprom_read_dword(n);
												ultoa(var2, Code, 10);
												ultoa(c, Num, 10);
												lcdClear();
												_delay_ms(30);
												for(ii=0; ii<=1000; ii++)
												{	
													lcdGotoXY(0,0);
													lcdPuts("No.");
													lcdGotoXY(0,3);
													lcdPuts(Num);
													lcdGotoXY(0,6);
													lcdPuts("*:Next");
													lcdGotoXY(1,0);
													lcdPuts("Code-");
													lcdGotoXY(1,6);
													lcdPuts(Code);
													if(scan_key()==10)
													{
														break;
													}
													if(scan_key()==12)
													{
														//_delay_ms(30);
														cc = 1;
														lcdClear();
														_delay_ms(30);
														for(i=0; i<=100; i++)
														{
															//_delay_ms(30);
															lcdGotoXY(1,4); 
															lcdPuts("Returned");
															//красный светодиод
															PORTB |=(1<<6);    //высокий уровень
															_delay_ms(30);
														}
														PORTB &= ~(1<<6);    //низкий уровень
														break;
													}
													_delay_ms(30);
												}
											}
										}
									}
//--------------------------------------------------------------------------							
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<=200; ii++)
									{
										itoa(c, Num, 10);
										lcdGotoXY(0,0);
										lcdPuts("Found");
										lcdGotoXY(0,7);
										lcdPuts(Num);
										lcdGotoXY(0,11);
										lcdPuts("codes");
										//PORTB |=(1<<5);    //высокий уровень 
										//_delay_ms(100);
										//PORTB = 0x00;
										//_delay_ms(10);
										_delay_ms(30);
									}
									i = 0;
									lcdClear();
									_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==1) 
								{
									//_delay_ms(30);
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<=6000; ii++)
									{
										lcdGotoXY(0,0);
										lcdPuts("*:Change-");
										Code_Copy = atol(Code);
										lcdGotoXY (0,10);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<5; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {Code[j]='0'; ff++;}
												else if(scan_key()==1) {Code[j]='1'; ff++;}
												else if(scan_key()==2) {Code[j]='2'; ff++;}
												else if(scan_key()==3) {Code[j]='3'; ff++;}
												else if(scan_key()==4) {Code[j]='4'; ff++;}
												else if(scan_key()==5) {Code[j]='5'; ff++;}
												else if(scan_key()==6) {Code[j]='6'; ff++;}
												else if(scan_key()==7) {Code[j]='7'; ff++;}
												else if(scan_key()==8) {Code[j]='8'; ff++;}
												else if(scan_key()==9) {Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==10) 
										{
											//_delay_ms(30);
											if(Code[4]!=0) 
											{
												if (Code[0] != 0)
												{
													n = 0;
													eeprom_busy_wait();
													eeprom_write_dword(n, Code_Copy);
													lcdClear();
													_delay_ms(30);
													for(iii=0; iii<=100; iii++)
													{
														lcdGotoXY(1,5);
														lcdPuts("Changed");
														//зеленый светодиод
														//PORTB |=(1<<5);    //высокий уровень
														_delay_ms(30);
													}
													//PORTB = 0x00;
													i = 0;
													break;
												}
											}
											else 
											{
												//memset(Code, 0, sizeof Code);//----------
												lcdClear();
												_delay_ms(30);
												for(iii=0; iii<=100; iii++)
												{
													lcdGotoXY(1,1); 
													lcdPuts("Min. 5 number");
													//красный светодиод
													PORTB |=(1<<6);    //высокий уровень
													_delay_ms(30);
												}
												PORTB &= ~(1<<6);    //низкий уровень
												lcdClear();
												_delay_ms(30);
											}
										}
//--------------------------------------------------------------------------								
										if(scan_key()==12)
										{
											//_delay_ms(30);
											Code[ff] = 0;
											ff--;
											for(iii=0; iii<=1; iii++)
											{
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(30);
											}
											PORTB &= ~(1<<6);    //низкий уровень
											lcdClear();
											_delay_ms(30);
										}
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}
								_delay_ms(30);
							}
						}
						//memset(Result, 0, sizeof Result);//------------------
						//f = -1;//------------------
						break;
						lcdClear();
						_delay_ms(30);
					}
					else  if (Result[4] == 0) 
					{
						//memset(Result, 0, sizeof Code);//----------
						lcdClear();
						_delay_ms(30);
						for(i=0; i<=100; i++)
						{
							lcdGotoXY(1,1); 
							lcdPuts("Min. 5 number");
							//красный светодиод
							PORTB |=(1<<6);    //высокий уровень
							_delay_ms(30);
						}
						PORTB &= ~(1<<6);    //низкий уровень
						lcdClear();
						_delay_ms(30);
					}
				}
////////////////////////////////////////////////////////////////////////////			
				if(scan_key()==12)
				{
					//_delay_ms(30);
					Result[f] = 0;
					f--;
					for(i=0; i<=1; i++)
					{
						//красный светодиод
						PORTB |=(1<<6);    //высокий уровень
						_delay_ms(30);
					}
					PORTB &= ~(1<<6);    //низкий уровень
					lcdClear();
					_delay_ms(30);
				}
////////////////////////////////////////////////////////////////////////////			
				_delay_ms(10);		
			}
		}
		else if (cycle > 0)
		{
			//Выключаем порт реле
			PORTB &= ~(1<<4);    //низкий уровень
			_delay_ms(30);
			if (cycle == 100)
			{
				cycle = 1;
			}
		}
		cycle++;
	}
}