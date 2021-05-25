#include "main.h"

//—————————————-

int main (void)
{	
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
	PORTD = 0xF0; // Устанавливаем лог. 1 в порт ввода
	_delay_ms(10);
	
	DDRB |=(1<<4);    //инициализируем как вход
	DDRB |=(1<<5);    //инициализируем как вход
	DDRB |=(1<<6);    //инициализируем как вход
	_delay_ms(10);
	
	lcdInit();
	lcdSetDisplay(LCD_DISPLAY_ON);
	lcdSetCursor(LCD_CURSOR_OFF);
	lcdClear();
	
	uint32_t mem = 11111;
	uint32_t adr = 0;
	eeprom_busy_wait();
	eeprom_update_dword(adr, mem);
	
	uint32_t mem2 = 22222;
	uint32_t adr2 = 4;
	eeprom_busy_wait();
	eeprom_update_dword(adr2, mem2);

	//char Result[5] = ""; 
	//char Code[5] = "";
	//int Result_Copy = 0;
	//int Code_Copy = 0;
	//uint8_t var = 0;
	//uint8_t var2 = 0;
	//char *Read_Number_Str = "";
	//char *j_str = "";
	//char *Key_str = "";
	unsigned short m; // объявляем переменную для цикла
	unsigned short i; // объявляем переменную для цикла
	unsigned short ii; // объявляем переменную для цикла
	unsigned short iii; // объявляем переменную для цикла
	unsigned short j; // объявляем переменную для цикла
	uint32_t n = 0;
	uint8_t nn = 0;
	char Result[7] = ""; 
	char Code[7] = "";
	uint32_t Result_Copy = 0;
	uint32_t Code_Copy = 0;
	uint32_t var = 0;
	uint32_t var2 = 0;
	
	
	while(1) 
	{
		memset(Result, 0, sizeof Result);
		memset(Code, 0, sizeof Code);
		Result_Copy = 0;
		Code_Copy = 0;
		var = 0;
		lcdClear();
		for(m=0; m<300; m++)
		{
			lcdGotoXY(0,0); 
			lcdPuts("Enter code:"); 
			// Выводим значение нажатой кнопки на индикатор
			for (j=0; j<7; j++)
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
							lcdGotoXY(1,5); 
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
				
				eeprom_busy_wait();
				var = eeprom_read_dword(0);
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
							_delay_ms(100);
							lcdClear();
							for(ii=0; ii<=100; ii++)
							{
								lcdGotoXY(0,0);
								lcdPuts("*:Add-");
								// Выводим значение нажатой кнопки на индикатор
								for (j=0; j<7; j++)
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
										//uint8_t nn = n;
										nn = n;
										eeprom_busy_wait();
										var2 = eeprom_read_byte(nn);
										if (var2 == 0xFF)
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
								lcdGotoXY (0,7);
								lcdPuts(Code);
								_delay_ms(10);
							}
						}
						memset(Result, 0, sizeof Result);
						memset(Code, 0, sizeof Code);
						Result_Copy = 0;
						Code_Copy = 0;
						var = 0;
						_delay_ms(10);
					}
				}
				_delay_ms(100);
				break;
			}
			
			if(scan_key()==12)
			{
				_delay_ms(100);
				lcdClear();
				for(i=0; i<=5; i++)
				{
					lcdGotoXY(1,5); 
					lcdPuts("Cleaned");
					//красный светодиод
					PORTB |=(1<<6);    //высокий уровень
					_delay_ms(100);
				}
				PORTB = 0x00;
				_delay_ms(10);
				break;
			}
			
			Result_Copy = atoi(Result);
			lcdGotoXY(1,0); 
			lcdPuts(Result); 
			_delay_ms(10);
				
	/*									lcdGotoXY(0,1);
										lcdPuts("*:Delete-");
										lcdGotoXY(0,10);
										lcdPuts(Code);
										lcdGotoXY(1,1);
										lcdPuts("#:Cancel");
										//sleep(50);
										//goto Return;
										
												//Удаление из массива
												while (i <= 123)
												{
													i++;
													Read_Number = EEPROM_read(i);
													if (Read_Number = (int)Code) 
													{
														EEPROM_write(i, 4294967295);	
														lcdGotoXY(1,5);
														lcdPuts("Deleted");
														//зеленый светодиод
														DDRB &=~(1<<5);    //инициализируем как вход
														PORTB |=(1<<5);    //высокий уровень 
														//sleep(5);															
														_delay_ms(5000);
														goto Return;
													}
												}
												goto Del;
											}
										}
											
										else if (Key_str == "#") 
										{
											goto Return;
										}
										Code_Copy = Code;
											
									}
									//красный светодиод
									DDRB &=~(1<<6);    //инициализируем как вход
									PORTB |=(1<<6);    //высокий уровень
									//sleep(1);																						
									_delay_ms(1000);
									goto Del;
								}	
									
								else if (Key_str == "0") 
								{
									Next:;
									i = 0;
									j = 0;
									j_str = "0";
									Read_Number_Str = "";
									Read_Number = EEPROM_read(0);
									lcdGotoXY(0,1);
									//lcdPuts j + ")" + Read_Number;
									itoa(j, j_str, 10);
									lcdPuts(j_str);
									lcdGotoXY(0,2);
									lcdPuts(")");
									lcdGotoXY(0,3);
									itoa(Read_Number, Read_Number_Str, 10);
									lcdPuts(Read_Number_Str);
									lcdGotoXY(0,10);
									lcdPuts("*:Next");
									lcdGotoXY(1,1);
									lcdPuts("#:Cancel");
									//sleep(50);
									//goto Return;
									//перебор массива
									while (i <= 123)
									{
												
											  
																										
											
											
										if (Key_str == "*") 
										{
											i++;
											j++;
											Read_Number = EEPROM_read(i);
											while (Read_Number = 4294967295)
											{
												i++;
												Read_Number = EEPROM_read(i);
											}
											lcdGotoXY(0,1);
											//lcdPuts j + ")" + Read_Number;
											itoa(j, j_str, 10);
											lcdPuts(j_str);
											lcdGotoXY(0,2);
											lcdPuts(")");
											lcdGotoXY(0,3);
											itoa(Read_Number, Read_Number_Str, 10);
											lcdPuts(Read_Number_Str);
											lcdGotoXY(0,10);
											lcdPuts("*:Next");
											lcdGotoXY(1,1);
											lcdPuts("#:Cancel");
											//sleep(50);
											//goto Return;
										}	
											
										else if (Key_str == "#") 
										{
											goto Return;
										}
										
									}
									goto Next;
								}
								
								else if (Key_str == "1") 
								{
									Change:;
									m = 0;
									while ((int)Code_Copy / 1000000 <= 1)
									{
										lcdGotoXY(0,1);
										lcdPuts("*:Change-");
										lcdGotoXY(0,7);
										lcdPuts(Code);
										lcdGotoXY(1,1);
										lcdPuts("#:Cancel");
										//sleep(50);
										//goto Return;
										
											
																													
											
											
										if (Key_str != "*" || Key_str != "#")
										{
											if (m < 1)
											{
												if (Code != "0")
												{
													strcat(Code, Key_str);
												}
											}
											else 
											{
												strcat(Code, Key_str);
											}
										}
										m++;
											
										if (Key_str == "*") 
										{
											if ((int)Code_Copy / 100000 >= 1)
											{
												//Перезапись переменной
												EEPROM_write(0, (int)Code);
												lcdGotoXY(1,5);
												lcdPuts("Changed");
												//зеленый светодиод
												DDRB &=~(1<<5);    //инициализируем как вход
												PORTB |=(1<<5);    //высокий уровень 
												//sleep(5);																	
												_delay_ms(5000);
												goto Return;
											}
										}
												
										else if (Key_str == "#") 
										{
											goto Return;
										}
										Code_Copy = Code;
											
									}
									//красный светодиод
									DDRB &=~(1<<6);    //инициализируем как вход
									PORTB |=(1<<6);    //высокий уровень
									//sleep(1);																	
									_delay_ms(1000);
									goto Change;
								}
								
							}
						}
					}
				}
					
				else if (Key_str  ==  "#")  
				{
					lcdGotoXY(1,5); 
					lcdPuts("RETURN");
					//красный светодиод
					DDRB &=~(1<<6);    //инициализируем как вход
					PORTB |=(1<<6);    //высокий уровень
					//sleep(5);																		
					_delay_ms(5000);
					goto Return; 
				}

			}*/
			
			//Result_Copy = Result - "0";
			
			//Result_Copy++;
			
			//Key_str = "";
			
			//DDRB &=~(1<<6);    //инициализируем как вход
			//PORTB |=(1<<6);    //высокий уровень	 
		}
	}
}