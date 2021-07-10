#include "main.h"

//—————————————-

int main (void)
{	
//--------------------------------------------------------------------------
	oneWireInit(PINB2);
	double temperature;
//--------------------------------------------------------------------------
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
//--------------------------------------------------------------------------	
	DDRB |= (1<<1);    //инициализируем как вход
	DDRB |= (1<<2);    //инициализируем как вход
	DDRB |= (1<<3);    //инициализируем как вход
	DDRB |= (1<<4);    //инициализируем как вход
	DDRB |= (1<<5);    //инициализируем как вход
	DDRB |= (1<<6);    //инициализируем как вход
//--------------------------------------------------------------------------	
	PORTD = 0xF0; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);
	lcdInit();
	_delay_ms(10);
	lcdSetCursor(LCD_CURSOR_OFF);
	_delay_ms(10);
	lcdSetDisplay(LCD_DISPLAY_ON);
	_delay_ms(10);
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
//--------------------------------------------------------------------------	
////////////////////////////////////////////////////////////////////////////		
//--------------------------------------------------------------------------	
	while(1) 
	{
		temperature = getTemp();
		char text[17] = "T = ";
		int fs[2];
		char num[5];
		explodeDoubleNumber(fs, temperature);
		if (temperature < 0) 
		{
			strcat(text, "-");
		}
		itoa(fs[0], num, 10);
		strcat(text, num);
		strcat(text, ".");
		itoa(fs[1], num, 10);
		strcat(text, num);
		strcat(text, "'C");
////////////////////////////////////////////////////////////////////////////		
		memset(Result, 0, sizeof Result);//------------------
		f = -1;//------------------
		lcdClear();
		_delay_ms(50);	
////////////////////////////////////////////////////////////////////////////		
		for(m=0; m<450; m++)
		{ 	
			lcdGotoXY(0, 0);
			lcdPuts(text);
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
			if (PINB & (1<<PB4)) 
			{
				while(PINB & (1<<PB4))
				{
					if (!PINB & (1<<PB4)) 
					{
						break;
					}	
				}	
				lcdClear();
				_delay_ms(50);
				for(j=0; j<=20; j++)
				{
					lcdGotoXY(1,4); 
					lcdPuts("Unlocked"); 
					//Включаем порт реле
					//PORTB |=(1<<4);    //высокий уровень
					//зеленый светодиод
					PORTB |=(1<<5);    //высокий уровень 
					_delay_ms(100);
				}
				PORTB = 0x00;
				break;
			}
////////////////////////////////////////////////////////////////////////////			
			if(scan_key()==10)  
			{
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
							_delay_ms(50);
							for(j=0; j<=20; j++)
							{
								lcdGotoXY(1,4); 
								lcdPuts("Unlocked"); 
								//Включаем порт реле
								//PORTB |=(1<<4);    //высокий уровень
								//зеленый светодиод
								PORTB |=(1<<5);    //высокий уровень 
								_delay_ms(100);
							}
							PORTB = 0x00;
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
						_delay_ms(50);
						for(i=0; i<=60; i++)
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
								//_delay_ms(30);
								lcdClear();
								_delay_ms(50);
								for(ii=0; ii<=300; ii++)
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
													_delay_ms(20);
													for(iii=0; iii<=5; iii++)
													{
														lcdGotoXY(1,5);
														lcdPuts("Added");
														//зеленый светодиод
														PORTB |=(1<<5);    //высокий уровень
														_delay_ms(100);
													}
													PORTB = 0x00;
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
											for(iii=0; iii<=5; iii++)
											{
												lcdGotoXY(1,1); 
												lcdPuts("Min. 5 number");
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(100);
											}
											PORTB = 0x00;
											lcdClear();
											_delay_ms(50);
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
										PORTB = 0x00;
										lcdClear();
									}
									_delay_ms(10);
								}
								lcdClear();
								_delay_ms(50);
							}
////////////////////////////////////////////////////////////////////////////						
							if (scan_key()==12) 
							{
								//_delay_ms(30);
								lcdClear();
								_delay_ms(50);
								for(ii=0; ii<=300; ii++)
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
													_delay_ms(50);
													for(iii=0; iii<=5; iii++)
													{
														lcdGotoXY(1,4);
														lcdPuts("Deleted");
														//зеленый светодиод
														PORTB |=(1<<5);    //высокий уровень
														_delay_ms(100);
													}
													PORTB = 0x00;
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
											_delay_ms(50);
											for(iii=0; iii<=5; iii++)
											{
												lcdGotoXY(1,1); 
												lcdPuts("Min. 5 number");
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(100);
											}
											PORTB = 0x00;
											lcdClear();
											_delay_ms(50);
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
										PORTB = 0x00;
										lcdClear();
									}
									_delay_ms(10);
								}
								lcdClear();
								_delay_ms(50);
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
											_delay_ms(50);
											for(ii=0; ii<=300; ii++)
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
													_delay_ms(50);
													for(i=0; i<=5; i++)
													{
														_delay_ms(50);
														lcdGotoXY(1,4); 
														lcdPuts("Returned");
														//красный светодиод
														PORTB |=(1<<6);    //высокий уровень
														_delay_ms(100);
													}
													PORTB = 0x00;
													break;
												}
												_delay_ms(10);
											}
										}
									}
								}
//--------------------------------------------------------------------------							
								lcdClear();
								_delay_ms(50);
								for(ii=0; ii<=5; ii++)
								{
									itoa(c, Num, 10);
									lcdGotoXY(0,0);
									lcdPuts("Found");
									lcdGotoXY(0,7);
									lcdPuts(Num);
									lcdGotoXY(0,11);
									lcdPuts("codes");
									PORTB |=(1<<5);    //высокий уровень 
									_delay_ms(100);
									PORTB = 0x00;
									_delay_ms(10);
								}
								i = 0;
								lcdClear();
								_delay_ms(50);
							}
////////////////////////////////////////////////////////////////////////////						
							if (scan_key()==1) 
							{
								//_delay_ms(30);
								lcdClear();
								_delay_ms(50);
								for(ii=0; ii<=300; ii++)
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
											n = 0;
											eeprom_busy_wait();
											eeprom_write_dword(n, Code_Copy);
											lcdClear();
											_delay_ms(50);
											for(iii=0; iii<=5; iii++)
											{
												lcdGotoXY(1,5);
												lcdPuts("Changed");
												//зеленый светодиод
												PORTB |=(1<<5);    //высокий уровень
												_delay_ms(100);
											}
											PORTB = 0x00;
											i = 0;
											break;
										}
										else 
										{
											//memset(Code, 0, sizeof Code);//----------
											lcdClear();
											_delay_ms(50);
											for(iii=0; iii<=5; iii++)
											{
												lcdGotoXY(1,1); 
												lcdPuts("Min. 5 number");
												//красный светодиод
												PORTB |=(1<<6);    //высокий уровень
												_delay_ms(100);
											}
											PORTB = 0x00;
											lcdClear();
											_delay_ms(50);
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
										PORTB = 0x00;
										lcdClear();
									}
									_delay_ms(10);
								}
								lcdClear();
								_delay_ms(50);
							}
							_delay_ms(10);
						}
					}
					//memset(Result, 0, sizeof Result);//------------------
					//f = -1;//------------------
					break;
					lcdClear();
					_delay_ms(50);
				}
				else  if (Result[4] == 0) 
				{
					//memset(Result, 0, sizeof Code);//----------
					lcdClear();
					_delay_ms(50);
					for(i=0; i<=5; i++)
					{
						lcdGotoXY(1,1); 
						lcdPuts("Min. 5 number");
						//красный светодиод
						PORTB |=(1<<6);    //высокий уровень
						_delay_ms(100);
					}
					PORTB = 0x00;
					lcdClear();
					_delay_ms(50);
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
				PORTB = 0x00;
				lcdClear();
				_delay_ms(50);
			}
////////////////////////////////////////////////////////////////////////////			
			_delay_ms(10);		
		}
	}
}