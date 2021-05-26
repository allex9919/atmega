#include "main.h"

//—————————————-

int main (void)
{	
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
	
	DDRB |=(1<<4);    //инициализируем как вход
	DDRB |=(1<<5);    //инициализируем как вход
	DDRB |=(1<<6);    //инициализируем как вход
	
	PORTD = 0xF0; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);
	lcdInit();
	_delay_ms(10);
	
	uint32_t mem = 11111;
	uint32_t adr = 0;
	eeprom_busy_wait();
	eeprom_update_dword(adr, mem);
	
	uint32_t mem2 = 22222;
	uint32_t adr2 = 4;
	eeprom_busy_wait();
	eeprom_update_dword(adr2, mem2);

	unsigned short m; // объявляем переменную для цикла
	unsigned short i; // объявляем переменную для цикла
	unsigned short ii; // объявляем переменную для цикла
	unsigned short iii; // объявляем переменную для цикла
	unsigned short j; // объявляем переменную для цикла
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
	unsigned int c2 = 0;
	char Num[4] = "";
	
	
	while(1) 
	{
		if(scan_key()==12)
		{
			lcdSetDisplay(LCD_DISPLAY_ON);
			_delay_ms(10);
			lcdSetCursor(LCD_CURSOR_OFF);
			_delay_ms(10);

			memset(Result, 0, sizeof Result);
			memset(Code, 0, sizeof Code);
			Result_Copy = 0;
			Code_Copy = 0;
			var = 0;
			//lcdClear();
			
			for(m=0; m<600; m++)
			{
				lcdGotoXY(0,0); 
				lcdPuts("Enter code:"); 
				// Выводим значение нажатой кнопки на индикатор
				for (j=0; j<5; j++)
				{
					if (Result[j]==0)
					{
						if(scan_key()==11) Result[j]='0';
						else if(scan_key()==1) Result[j]='1';
						else if(scan_key()==2) Result[j]='2';
						else if(scan_key()==3) Result[j]='3';
						else if(scan_key()==4) Result[j]='4';
						else if(scan_key()==5) Result[j]='5';
						else if(scan_key()==6) Result[j]='6';
						else if(scan_key()==7) Result[j]='7';
						else if(scan_key()==8) Result[j]='8';
						else if(scan_key()==9) Result[j]='9';
						break;
					}
				}
				
				if(scan_key()==10)  
				{
					for (n=4; n<129; n+=4)
					{
						eeprom_busy_wait();
						var = eeprom_read_dword(n);
						if  (Result_Copy  ==  var) 
						{ 
							_delay_ms(100);
							lcdClear();
							for(j=0; j<=10; j++)
							{
								lcdGotoXY(1,4); 
								lcdPuts("Unlocked"); 
								//Включаем порт реле
								PORTB |=(1<<4);    //высокий уровень
								//зеленый светодиод
								PORTB |=(1<<5);    //высокий уровень 
								_delay_ms(100);
							}
							PORTB = 0x00;
							break;
						}
					}
					
					n = 0;
					eeprom_busy_wait();
					var = eeprom_read_dword(n);
					if (Result_Copy == var)  
					{
						_delay_ms(100);
						lcdClear();
						for(i=0; i<=30; i++)
						{
							Code_Copy = 0;
							lcdGotoXY(0,0);
							lcdPuts("*:Add/#:Delete");
							lcdGotoXY(1,0);
							lcdPuts("0:List/1:Change");
							if (scan_key()==10) 
							{
								memset(Code, 0, sizeof Code);
								Code_Copy = 0;
								_delay_ms(100);
								lcdClear();
								for(ii=0; ii<=300; ii++)
								{
									lcdGotoXY(0,0);
									lcdPuts("*:Add-");
									// Выводим значение нажатой кнопки на индикатор
									for (j=0; j<5; j++)
									{
										if (Code[j]==0)
										{
											if(scan_key()==11) Code[j]='0';
											else if(scan_key()==1) Code[j]='1';
											else if(scan_key()==2) Code[j]='2';
											else if(scan_key()==3) Code[j]='3';
											else if(scan_key()==4) Code[j]='4';
											else if(scan_key()==5) Code[j]='5';
											else if(scan_key()==6) Code[j]='6';
											else if(scan_key()==7) Code[j]='7';
											else if(scan_key()==8) Code[j]='8';
											else if(scan_key()==9) Code[j]='9';
											break;
										}
									}
									if(scan_key()==10) 
									{
										var3 = 0;
										for(n=4; n<129; n+=4)
										{
											nn = n;
											eeprom_busy_wait();
											var3 = eeprom_read_byte(nn);
											if (var3 == 0xFF)
											{
												eeprom_busy_wait();
												eeprom_update_dword(n, Code_Copy);
												_delay_ms(100);
												lcdClear();
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
										break;
									}
									
									if(scan_key()==12)
									{
										memset(Code, 0, sizeof Code);
										_delay_ms(100);
										lcdClear();
										for(iii=0; iii<=5; iii++)
										{
											lcdGotoXY(1,4); 
											lcdPuts("Cleaned");
											//красный светодиод
											PORTB |=(1<<6);    //высокий уровень
											_delay_ms(100);
										}
										PORTB = 0x00;
										lcdClear();
										//break;
									}
									
									Code_Copy = atoi(Code);
									lcdGotoXY (0,7);
									lcdPuts(Code);
									_delay_ms(10);
								}
								lcdClear();
							}
							if (scan_key()==12) 
							{
								memset(Code, 0, sizeof Code);
								Code_Copy = 0;
								_delay_ms(100);
								lcdClear();
								for(ii=0; ii<=300; ii++)
								{
									lcdGotoXY(0,0);
									lcdPuts("*:Delete-");
									// Выводим значение нажатой кнопки на индикатор
									for (j=0; j<5; j++)
									{
										if (Code[j]==0)
										{
											if(scan_key()==11) Code[j]='0';
											else if(scan_key()==1) Code[j]='1';
											else if(scan_key()==2) Code[j]='2';
											else if(scan_key()==3) Code[j]='3';
											else if(scan_key()==4) Code[j]='4';
											else if(scan_key()==5) Code[j]='5';
											else if(scan_key()==6) Code[j]='6';
											else if(scan_key()==7) Code[j]='7';
											else if(scan_key()==8) Code[j]='8';
											else if(scan_key()==9) Code[j]='9';
											break;
										}
									}
									if(scan_key()==10) 
									{
										var2 = 0;
										for(n=4; n<129; n+=4)
										{
											eeprom_busy_wait();
											var2 = eeprom_read_dword(n);
											if (Code_Copy == var2)
											{
												nn = n;
												eeprom_busy_wait();
												eeprom_update_byte(nn, 0xFF);
												nn++;
												eeprom_busy_wait();
												eeprom_update_byte(nn, 0xFF);
												nn++;
												eeprom_busy_wait();
												eeprom_update_byte(nn, 0xFF);
												nn++;
												eeprom_busy_wait();
												eeprom_update_byte(nn, 0xFF);
												_delay_ms(100);
												lcdClear();
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
										memset(Code, 0, sizeof Code);
										break;
									}
									
									if(scan_key()==12)
									{
										memset(Code, 0, sizeof Code);
										_delay_ms(100);
										lcdClear();
										for(iii=0; iii<=5; iii++)
										{
											lcdGotoXY(1,5); 
											lcdPuts("Cleaned");
											//красный светодиод
											PORTB |=(1<<6);    //высокий уровень
											_delay_ms(100);
										}
										PORTB = 0x00;
										lcdClear();
										//break;
									}
									
									Code_Copy = atoi(Code);
									lcdGotoXY (0,10);
									lcdPuts(Code);
									_delay_ms(10);
								}
								lcdClear();
							}
							if (scan_key()==11) 
							{
								var2 = 0;
								var3 = 0;
								c = 0;
								c2 = 0;
								for(n=4; n<129; n+=4)
								{
									memset(Code, 0, sizeof Code);
									memset(Num, 0, sizeof Num);
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
										if (c2 == 0)
										{
											eeprom_busy_wait();
											var2 = eeprom_read_dword(n);
											utoa(var2, Code, 10);
											utoa(c, Num, 10);
											_delay_ms(50);
											lcdClear();
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
													c2 = 1;
													_delay_ms(100);
													lcdClear();
													for(i=0; i<=5; i++)
													{
														_delay_ms(100);
														lcdGotoXY(1,4); 
														lcdPuts("Returned");
														//красный светодиод
														PORTB |=(1<<6);    //высокий уровень
														_delay_ms(100);
													}
													PORTB = 0x00;
													break;
												}
											}
											_delay_ms(10);
										}
									}
								}
								lcdClear();
								_delay_ms(100);
								for(ii=0; ii<=5; ii++)
								{
									itoa(c, Num, 10);
									lcdGotoXY(0,0);
									lcdPuts("Found");
									lcdGotoXY(0,7);
									lcdPuts(Num);
									lcdGotoXY(0,11);
									lcdPuts("codes");
									_delay_ms(100);
								}
								lcdClear();
							}
							if (scan_key()==1) 
							{
								memset(Code, 0, sizeof Code);
								Code_Copy = 0;
								_delay_ms(100);
								lcdClear();
								for(ii=0; ii<=300; ii++)
								{
									lcdGotoXY(0,0);
									lcdPuts("*:Change-");
									// Выводим значение нажатой кнопки на индикатор
									for (j=0; j<5; j++)
									{
										if (Code[j]==0)
										{
											if(scan_key()==11) Code[j]='0';
											else if(scan_key()==1) Code[j]='1';
											else if(scan_key()==2) Code[j]='2';
											else if(scan_key()==3) Code[j]='3';
											else if(scan_key()==4) Code[j]='4';
											else if(scan_key()==5) Code[j]='5';
											else if(scan_key()==6) Code[j]='6';
											else if(scan_key()==7) Code[j]='7';
											else if(scan_key()==8) Code[j]='8';
											else if(scan_key()==9) Code[j]='9';
											break;
										}
									}
									if(scan_key()==10) 
									{
										if (Code[0] != 0)
										{
											n = 0;
											eeprom_busy_wait();
											eeprom_update_dword(n, Code_Copy);
											_delay_ms(100);
											lcdClear();
											for(iii=0; iii<=5; iii++)
											{
												lcdGotoXY(1,5);
												lcdPuts("Changed");
												//зеленый светодиод
												PORTB |=(1<<5);    //высокий уровень
												_delay_ms(100);
											}
											PORTB = 0x00;
											break;
										}
									}
									if(scan_key()==12)
									{
										memset(Code, 0, sizeof Code);
										_delay_ms(100);
										lcdClear();
										for(iii=0; iii<=5; iii++)
										{
											lcdGotoXY(1,4); 
											lcdPuts("Cleaned");
											//красный светодиод
											PORTB |=(1<<6);    //высокий уровень
											_delay_ms(100);
										}
										PORTB = 0x00;
										lcdClear();
										//break;
									}
									
									Code_Copy = atoi(Code);
									lcdGotoXY (0,10);
									lcdPuts(Code);
									_delay_ms(10);
								}
								lcdClear();
							}
						}
					}
					memset(Result, 0, sizeof Result);
					Result_Copy = 0;
					var = 0;
					lcdClear();
					_delay_ms(100);
					//break;
				}
				
				if(scan_key()==12)
				{
					if (Result[0] != 0)
					{
						memset(Result, 0, sizeof Result);
						memset(Code, 0, sizeof Code);
						Result_Copy = 0;
						Code_Copy = 0;
						var = 0;
						_delay_ms(100);
						lcdClear();
						for(i=0; i<=5; i++)
						{
							lcdGotoXY(1,4); 
							lcdPuts("Cleaned");
							//красный светодиод
							PORTB |=(1<<6);    //высокий уровень
							_delay_ms(100);
						}
						PORTB = 0x00;
						lcdClear();
						//break;
					}
					else
					{
						break;
					}
				}
				
				Result_Copy = atoi(Result);
				lcdGotoXY(1,0); 
				lcdPuts(Result); 
				_delay_ms(10);		
			}
			
			lcdClear();
			_delay_ms(10);
			lcdSetDisplay(LCD_DISPLAY_OFF);
			_delay_ms(100);
		}
		_delay_ms(10);
	}
}