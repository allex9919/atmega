#include "main.h"

//—————————————

int main (void)
{	
//--------------------------------------------------------------------------	
	DDRD |= (1 << PD3)|(1 << PD2)|(1 << PD1)|(1 << PD0); // Порт вывода
	DDRD &= ~(1 << PD7)|(1 << PD6)|(1 << PD5)|(1 << PD4); // Порт ввода
	PORTD = 0xf0; // Устанавливаем лог. 1 в порт ввода
	_delay_us(10);
//--------------------------------------------------------------------------	
	DDRB |=(1<<3);    //инициализируем как выход
	DDRB |=(1<<4);    //инициализируем как выход
	DDRB |=(1<<5);    //инициализируем как выход
	DDRB |=(1<<6);    //инициализируем как выход
	DDRB |=(1<<7);	  //инициализируем как выход
//--------------------------------------------------------------------------		
	/*uint32_t mem1 = 0;
	uint32_t adr1 = 0;
	eeprom_busy_wait();
	eeprom_write_dword(adr1, mem1);
//--------------------------------------------------------------------------	
	uint32_t mem2 = 0;
	uint32_t adr2 = 4;
	eeprom_busy_wait();
	eeprom_write_dword(adr2, mem2);
//--------------------------------------------------------------------------		
	uint32_t mem3 = 1111;
	uint32_t adr3 = 8;
	eeprom_busy_wait();
	eeprom_write_dword(adr3, mem3);
//--------------------------------------------------------------------------	
	uint32_t mem4 = 2222;
	uint32_t adr4 = 12;
	eeprom_busy_wait();
	eeprom_write_dword(adr4, mem4);*/
//--------------------------------------------------------------------------	
	uint32_t all_on;
	eeprom_busy_wait();
	all_on = eeprom_read_dword(0);
	if (all_on == 999)
	{
		all_on = 0;
	}
//--------------------------------------------------------------------------	
	uint32_t period_on;
	eeprom_busy_wait();
	period_on = eeprom_read_dword(4);
	if (period_on == 99)
	{
		period_on = 0;
	}
//--------------------------------------------------------------------------
	int z = 3; //Выбираем разрядность кода
	unsigned short zt = 200; //Выбираем задержку при delay(30)
	unsigned short ct = 500; //Выбираем задержку при delay(10)
	unsigned short ct2 = 500;
	unsigned short ct22 = ct2 - 1;
	unsigned short ct3 = 200;
	unsigned short m; // объявляем переменную для цикла
	unsigned short i; // объявляем переменную для цикла
	unsigned short ii; // объявляем переменную для цикла
	unsigned short iii; // объявляем переменную для цикла
	unsigned short j; // объявляем переменную для цикла
	short f = -1; 
	short ff; 
	uint32_t n;
	uint8_t nn;
	char Result[6] = ""; 
	char Code[6];
	int Result_Copy = 0;
	uint32_t Code_Copy = 0;
	uint32_t var;
	uint32_t var2;
	uint8_t var3;
	unsigned int c;
	unsigned int cc;
	char Num[4];
	int cycle = 0;
	int cycle2 = 0; 
	char text1[16] = "";
	char text2[16] = "";
	//char text3[16] = "";
	uint8_t ti;
	//char txt[16] = "";
	char all_var[4] = "";
	char period_var[3] = "";
	//unsigned short an; 
	//unsigned short anim;	
	unsigned short r = 0;
	int flag = 0; 
//--------------------------------------------------------------------------	
////////////////////////////////////////////////////////////////////////////		
//--------------------------------------------------------------------------	
	while(1) 
	{	
		PORTB |=(1<<7);
		if (cycle == 0)
		{
			PORTB &= ~(1<<6);    //низкий уровень
			//Включаем порт реле
			PORTB |=(1<<4);    //высокий уровень
			//for(j=0; j<=33; j++)
			//{
				_delay_ms(30);
			//}	
////////////////////////////////////////////////////////////////////////////
			if (cycle2 == 0)
			{	
				cycle2 = 1;
////////////////////////////////////////////////////////////////////////////				
				lcdInit();
				_delay_ms(10);
				lcdSetCursor(LCD_CURSOR_OFF);
				_delay_ms(10);
				lcdSetDisplay(LCD_DISPLAY_ON);
				_delay_ms(10);		
////////////////////////////////////////////////////////////////////////////				
				double temperature;
				uint8_t tn = 8;
				uint64_t roms[tn];
				oneWireInit(PINB2);
				searchRom(roms, &tn);
				_delay_ms(30);				
////////////////////////////////////////////////////////////////////////////
				//strcat(txt, "Detect ");
				//char num[5];
				//itoa(tn, num, 10);
				//strcat(txt, num);
				//strcat(txt, " devices");				
				//lcdGotoXY(1, 0);
				//lcdPuts(txt);
				//_delay_ms(500);
////////////////////////////////////////////////////////////////////////////				
				utoa(all_on, all_var, 10);
				utoa(period_on, period_var, 10);
				for (ti = 0; ti < 3; ti++)
				{
					if (ti == 0)
					{
						lcdGotoXY(1, 6);
						lcdPuts("/(^-^)/");
					}
					else if (ti == 1)
					{
						lcdGotoXY(1, 6);
						lcdPuts("-(^-^)-");
					}
					else if (ti == 2)
					{
						lcdGotoXY(1, 6);
						lcdPuts("/(^-^)/");
					}
					/*if (scan_key()==10) 
					{
						while(scan_key()==10);
////////////////////////////////////////////////////////////////////////////						
						lcdClear();
						_delay_ms(10);
						for (anim = 0; anim < 3; anim++)
						{
							for (an = 0; an < 24; an++)
							{
								if (an == 0)
								{
									lcdGotoXY(0, 0);
									lcdPuts("");
									lcdGotoXY(1, 0);
									lcdPuts("________________");
								}
								else if (an == 1)
								{
									lcdGotoXY(0, 0);
									lcdPuts("");
									lcdGotoXY(1, 0);
									lcdPuts(")_______________");
								}
								else if (an == 2)
								{
									lcdGotoXY(0, 0);
									lcdPuts("_");
									lcdGotoXY(1, 0);
									lcdPuts("_)______________");
								}
								else if (an == 3)
								{
									lcdGotoXY(0, 0);
									lcdPuts("__");
									lcdGotoXY(1, 0);
									lcdPuts("0_)_____________");
								}
								else if (an == 4)
								{
									lcdGotoXY(0, 0);
									lcdPuts("/__");
									lcdGotoXY(1, 0);
									lcdPuts("_0_)____________");
								}
								else if (an == 5)
								{
									lcdGotoXY(0, 0);
									lcdPuts("_/__");
									lcdGotoXY(1, 0);
									lcdPuts("0_0_)___________");
								}
								else if (an == 6)
								{
									lcdGotoXY(0, 0);
									lcdPuts("__/__");
									lcdGotoXY(1, 0);
									lcdPuts("_0_0_)__________");
								}
								else if (an == 7)
								{
									lcdGotoXY(0, 0);
									lcdPuts(" __/__");
									lcdGotoXY(1, 0);
									lcdPuts("|_0_0_)_________");
								}
								else if (an == 8)
								{
									lcdGotoXY(0, 0);
									lcdPuts("  __/__");
									lcdGotoXY(1, 0);
									lcdPuts("_|_0_0_)________");
								}
								else if (an == 9)
								{
									lcdGotoXY(0, 0);
									lcdPuts("   __/__");
									lcdGotoXY(1, 0);
									lcdPuts("__|_0_0_)_______");
								}
								else if (an == 10)
								{
									lcdGotoXY(0, 0);
									lcdPuts("    __/__");
									lcdGotoXY(1, 0);
									lcdPuts("___|_0_0_)______");
								}
								else if (an == 11)
								{
									lcdGotoXY(0, 0);
									lcdPuts("     __/__");
									lcdGotoXY(1, 0);
									lcdPuts("____|_0_0_)_____");
								}
								else if (an == 12)
								{
									lcdGotoXY(0, 0);
									lcdPuts("      __/__");
									lcdGotoXY(1, 0);
									lcdPuts("_____|_0_0_)____");
								}
								else if (an == 13)
								{
									lcdGotoXY(0, 0);
									lcdPuts("       __/__");
									lcdGotoXY(1, 0);
									lcdPuts("______|_0_0_)___");
								}
								else if (an == 14)
								{
									lcdGotoXY(0, 0);
									lcdPuts("        __/__");
									lcdGotoXY(1, 0);
									lcdPuts("_______|_0_0_)__");
								}
								else if (an == 15)
								{
									lcdGotoXY(0, 0);
									lcdPuts("         __/__");
									lcdGotoXY(1, 0);
									lcdPuts("________|_0_0_)_");
								}
								else if (an == 16)
								{
									lcdGotoXY(0, 0);
									lcdPuts("          __/__");
									lcdGotoXY(1, 0);
									lcdPuts("_________|_0_0_)");
								}
								else if (an == 17)
								{
									lcdGotoXY(0, 0);
									lcdPuts("           __/__");
									lcdGotoXY(1, 0);
									lcdPuts("__________|_0_0_");
								}
								else if (an == 18)
								{
									lcdGotoXY(0, 0);
									lcdPuts("            __/_");
									lcdGotoXY(1, 0);
									lcdPuts("___________|_0_0");
								}
								else if (an == 19)
								{
									lcdGotoXY(0, 0);
									lcdPuts("             __/");
									lcdGotoXY(1, 0);
									lcdPuts("____________|_0_");
								}
								else if (an == 20)
								{
									lcdGotoXY(0, 0);
									lcdPuts("             __");
									lcdGotoXY(1, 0);
									lcdPuts("____________|_0");
								}
								else if (an == 21)
								{
									lcdGotoXY(0, 0);
									lcdPuts("              _");
									lcdGotoXY(1, 0);
									lcdPuts("_____________|_");
								}
								else if (an == 22)
								{
									//lcdGotoXY(0, 0);
									//lcdPuts("               ");
									lcdGotoXY(1, 0);
									lcdPuts("______________|");
								}
								else if (an == 23)
								{
									//lcdGotoXY(0, 0);
									//lcdPuts("               ");
									lcdGotoXY(1, 0);
									lcdPuts("_______________");
								}
								_delay_ms(100);
								lcdClear();
								_delay_ms(10);
							}
						}
						lcdClear();
						_delay_ms(10);
						ti--;
////////////////////////////////////////////////////////////////////////////						
						/*if (period_on == 0)
						{
							period_on = 1;
						}
						else
						{
							period_on = 0;
							eeprom_busy_wait();
							eeprom_write_dword(4, period_on);
							lcdClear();
							_delay_ms(10);
						}
					}*/
					//lcdGotoXY(0, 0);
					//lcdPuts(">");
					lcdGotoXY(0, 0);
					lcdPuts(period_var);
					lcdGotoXY(0, 6);
					lcdPuts("Hello!");
					//lcdGotoXY(0, 14);
					//lcdPuts("*:");
					//lcdGotoXY(1, 0);
					//lcdPuts(">");
					lcdGotoXY(1, 0);
					lcdPuts(all_var);
					//lcdGotoXY(1, 5);
					//lcdPuts("/(^_^)/");
					
					/*if (period_on != 0)
					{
						period_on++;
						eeprom_busy_wait();
						eeprom_write_dword(4, period_on);
						period_on--;
						ultoa(period_on, period_var, 10);
						lcdGotoXY(1, 14);
						lcdPuts(period_var);	
					}*/			
////////////////////////////////////////////////////////////////////////////					
					temperature = getTemp(roms[ti]);
					int fs[2];
					char num2[5];
					itoa(ti, num2, 10);
					//strcat(text, "T");
					//strcat(text, num2);
					//strcat(text, "=");
					explodeDoubleNumber(fs, temperature);
					if (fs[0]==0 && fs[1]==0)
					{
						continue;
					}
					if (ti == 0)
					{
						if (temperature < 0) 
						{
							strcat(text1, "-");
						}
						itoa(fs[0], num2, 10);
						strcat(text1, num2);
						strcat(text1, ".");
						itoa(fs[1], num2, 10);
						strcat(text1, num2);
						strcat(text1, "'C ");
					}
					if (ti == 1)
					{
						if (temperature < 0) 
						{
							strcat(text2, "-");
						}
						itoa(fs[0], num2, 10);
						strcat(text2, num2);
						strcat(text2, ".");
						itoa(fs[1], num2, 10);
						strcat(text2, num2);
						strcat(text2, "'C ");
					}
					/*if (ti == 2)
					{
						if (temperature < 0) 
						{
							strcat(text3, "-");
						}
						itoa(fs[0], num2, 10);
						strcat(text3, num2);
						strcat(text3, ".");
						itoa(fs[1], num2, 10);
						strcat(text3, num2);
						strcat(text3, "'C ");
					}*/
					_delay_ms(30);
					lcdClear();
					_delay_ms(10);
				}
			}
////////////////////////////////////////////////////////////////////////////			
			//memset(Result, 0, sizeof Result);//------------------
			//f = -1;//------------------
			//r = 0;
			lcdClear();
			_delay_ms(30);
////////////////////////////////////////////////////////////////////////////		
			for(m=0; m<ct2; m++)
			{ 
				/*if (PINB & (1<<PB3)) 
				{
					while(PINB & (1<<PB3));
					//{
						//if ((PINB & (1<<PB3)) == 0) 
						//{
							//break;
						//}	
					//}	
					//lcdClear();
					//_delay_ms(30);
					for(j=0; j<zt; j++)
					{
						//lcdGotoXY(1,4); 
						//lcdPuts("Unlocked"); 
						PORTB |=(1<<3);    //высокий уровень 
						PORTB |=(1<<5);    //высокий уровень 
						_delay_ms(30);
					}
					PORTB &= ~(1<<3);    //низкий уровень
					PORTB &= ~(1<<5);    //низкий уровень
					//lcdClear();
					//_delay_ms(30);
					//all_on--;
				}*/
////////////////////////////////////////////////////////////////////////////								
				//lcdGotoXY(0, 0);
				//lcdPuts(txt);
				//lcdGotoXY(0, 0);
				//lcdPuts(text3);
				lcdGotoXY(0, 9);
				lcdPuts(text1);
				lcdGotoXY(1, 9);
				lcdPuts(text2);
////////////////////////////////////////////////////////////////////////////
				lcdGotoXY(0,0); 
				lcdPuts("Code:"); 
				lcdGotoXY(1,0); 
				lcdPuts(">"); 
				Result_Copy = atol(Result);
				lcdGotoXY(1,1); 
				lcdPuts(Result); 
				if (f == -1)
				{
					lcdGotoXY(1,1); 
					lcdPuts("...."); 
				}
				else if (f == 0)
				{
					lcdGotoXY(1,2); 
					lcdPuts("...");	
				}
				else if (f == 1)
				{
					lcdGotoXY(1,3); 
					lcdPuts("..");	
				}
				else if (f == 2)
				{
					lcdGotoXY(1,4); 
					lcdPuts(".");	
				}
				else if (f == 3)
				{
					r = 1;
					_delay_ms(100);
				}
				
				//else if (f == 3)
				//{
					//lcdGotoXY(1,5); 
					//lcdPuts(".");	
				//}
				//lcdGotoXY(1,6); 
				//lcdPuts("]"); 
				// Выводим значение нажатой кнопки на индикатор
				for (j=0; j<=z; j++)
				{
					if (Result[j]==0)
					{
						if(scan_key()==11) {while(scan_key()==11); Result[j]='0'; f++;}
						else if(scan_key()==1) {while(scan_key()==1); Result[j]='1'; f++;}
						else if(scan_key()==2) {while(scan_key()==2); Result[j]='2'; f++;}
						else if(scan_key()==3) {while(scan_key()==3); Result[j]='3'; f++;}
						else if(scan_key()==4) {while(scan_key()==4); Result[j]='4'; f++;}
						else if(scan_key()==5) {while(scan_key()==5); Result[j]='5'; f++;}
						else if(scan_key()==6) {while(scan_key()==6); Result[j]='6'; f++;}
						else if(scan_key()==7) {while(scan_key()==7); Result[j]='7'; f++;}
						else if(scan_key()==8) {while(scan_key()==8); Result[j]='8'; f++;}
						else if(scan_key()==9) {while(scan_key()==9); Result[j]='9'; f++;}
						//_delay_ms(30);
						break;
					}
				}
////////////////////////////////////////////////////////////////////////////			
				if(r == 1)  
				{
					//while(scan_key()==10);
					//cycle--;
					//_delay_ms(30);
					if(Result[z]!=0) 
					{				
						n = 8;
						eeprom_busy_wait();
						var = eeprom_read_dword(n);
						if (Result_Copy == var)  
						{
							flag++;
							period_on++;
							eeprom_busy_wait();
							eeprom_write_dword(4, period_on);
							lcdClear();
							_delay_ms(30);
							for(i=0; i<ct3; i++)
							{
								memset(Code, 0, sizeof Code);//-------------
								c = 0;//----------
								cc = 0;//----------
								ff = -1;//----------
								lcdGotoXY(0,0);
								lcdPuts("*:Add/Change");
								lcdGotoXY(1,0);
								lcdPuts("#:Delete/0:List");
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==10) 
								{
									while(scan_key()==10);
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<ct; ii++)
									{
										lcdGotoXY(1,0);
										lcdPuts("*:Add #:Change");
										lcdGotoXY(0,0);
										lcdPuts(">");
										Code_Copy = atol(Code);
										lcdGotoXY (0,1);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<=z; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {while(scan_key()==11); Code[j]='0'; ff++;}
												else if(scan_key()==1) {while(scan_key()==1); Code[j]='1'; ff++;}
												else if(scan_key()==2) {while(scan_key()==2); Code[j]='2'; ff++;}
												else if(scan_key()==3) {while(scan_key()==3); Code[j]='3'; ff++;}
												else if(scan_key()==4) {while(scan_key()==4); Code[j]='4'; ff++;}
												else if(scan_key()==5) {while(scan_key()==5); Code[j]='5'; ff++;}
												else if(scan_key()==6) {while(scan_key()==6); Code[j]='6'; ff++;}
												else if(scan_key()==7) {while(scan_key()==7); Code[j]='7'; ff++;}
												else if(scan_key()==8) {while(scan_key()==8); Code[j]='8'; ff++;}
												else if(scan_key()==9) {while(scan_key()==9); Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==12) 
										{
											while(scan_key()==10);
											//_delay_ms(30);
											if(Code[z]!=0) 
											{
												n = 8;
												eeprom_busy_wait();
												eeprom_write_dword(n, Code_Copy);
												lcdClear();
												_delay_ms(30);
												for(iii=0; iii<=100; iii++)
												{
													lcdGotoXY(1,5);
													lcdPuts("Changed");
													//зеленый светодиод
													PORTB |=(1<<5);    //высокий уровень
													_delay_ms(30);
												}
												PORTB &= ~(1<<5);    //низкий уровень
												i = 0;
												break;
											}
										}
										if (scan_key()==10) 
										{
											while(scan_key()==10);
											//_delay_ms(30);
											if(Code[z]!=0) 
											{
												for(n=12; n<129; n+=4)
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
															PORTB |=(1<<5);    //высокий уровень
															_delay_ms(30);
														}
														PORTB &= ~(1<<5);    //низкий уровень
														break;
													}
												}
												i = 0;
												break;
											}
											/*else 
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
											}*/
										}
//--------------------------------------------------------------------------								
										/*if(scan_key()==12)
										{
											while(scan_key()==12);
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
										}*/
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==12) 
								{
									while(scan_key()==12);
									//_delay_ms(30);
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<ct; ii++)
									{
										lcdGotoXY(0,0);
										lcdPuts("*:Delete-");
										Code_Copy = atol(Code);
										lcdGotoXY (0,10);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<=z; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {while(scan_key()==11); Code[j]='0'; ff++;}
												else if(scan_key()==1) {while(scan_key()==1); Code[j]='1'; ff++;}
												else if(scan_key()==2) {while(scan_key()==2); Code[j]='2'; ff++;}
												else if(scan_key()==3) {while(scan_key()==3); Code[j]='3'; ff++;}
												else if(scan_key()==4) {while(scan_key()==4); Code[j]='4'; ff++;}
												else if(scan_key()==5) {while(scan_key()==5); Code[j]='5'; ff++;}
												else if(scan_key()==6) {while(scan_key()==6); Code[j]='6'; ff++;}
												else if(scan_key()==7) {while(scan_key()==7); Code[j]='7'; ff++;}
												else if(scan_key()==8) {while(scan_key()==8); Code[j]='8'; ff++;}
												else if(scan_key()==9) {while(scan_key()==9); Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==10) 
										{
											while(scan_key()==10);
											//_delay_ms(30);
											if(Code[z]!=0) 
											{
												for(n=12; n<129; n+=4)
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
															PORTB |=(1<<5);    //высокий уровень
															_delay_ms(30);
														}
														PORTB &= ~(1<<5);    //низкий уровень
														break;
													}
												}
												i = 0;
												break;
											}
											/*else 
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
											}*/
										}
//--------------------------------------------------------------------------								
										/*if(scan_key()==12)
										{
											while(scan_key()==12);
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
										}*/
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								if (scan_key()==11) 
								{
									while(scan_key()==11);
									//_delay_ms(30);
									for(n=12; n<129; n+=4)
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
												for(ii=0; ii<ct; ii++)
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
														while(scan_key()==10);
														break;
													}
													if(scan_key()==12)
													{
														/*while(scan_key()==12);
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
														PORTB &= ~(1<<6);    //низкий уровень*/
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
										PORTB |=(1<<5);    //высокий уровень 
										_delay_ms(30);
									}
									PORTB &= ~(1<<5);    //низкий уровень
									i = 0;
									lcdClear();
									//_delay_ms(30);
								}
////////////////////////////////////////////////////////////////////////////						
								/*if (scan_key()==1) 
								{
									while(scan_key()==1);
									//_delay_ms(30);
									lcdClear();
									_delay_ms(30);
									for(ii=0; ii<ct; ii++)
									{
										lcdGotoXY(0,0);
										lcdPuts("*:Change-");
										Code_Copy = atol(Code);
										lcdGotoXY (0,10);
										lcdPuts(Code);
										// Выводим значение нажатой кнопки на индикатор
										for (j=0; j<=z; j++)
										{
											if (Code[j]==0)
											{
												if(scan_key()==11) {while(scan_key()==11); Code[j]='0'; ff++;}
												else if(scan_key()==1) {while(scan_key()==1); Code[j]='1'; ff++;}
												else if(scan_key()==2) {while(scan_key()==2); Code[j]='2'; ff++;}
												else if(scan_key()==3) {while(scan_key()==3); Code[j]='3'; ff++;}
												else if(scan_key()==4) {while(scan_key()==4); Code[j]='4'; ff++;}
												else if(scan_key()==5) {while(scan_key()==5); Code[j]='5'; ff++;}
												else if(scan_key()==6) {while(scan_key()==6); Code[j]='6'; ff++;}
												else if(scan_key()==7) {while(scan_key()==7); Code[j]='7'; ff++;}
												else if(scan_key()==8) {while(scan_key()==8); Code[j]='8'; ff++;}
												else if(scan_key()==9) {while(scan_key()==9); Code[j]='9'; ff++;}
												//_delay_ms(30);
												break;
											}
										}
//--------------------------------------------------------------------------								
										if (scan_key()==10) 
										{
											while(scan_key()==10);
											//_delay_ms(30);
											if(Code[z]!=0) 
											{
												n = 8;
												eeprom_busy_wait();
												eeprom_write_dword(n, Code_Copy);
												lcdClear();
												_delay_ms(30);
												for(iii=0; iii<=100; iii++)
												{
													lcdGotoXY(1,5);
													lcdPuts("Changed");
													//зеленый светодиод
													PORTB |=(1<<5);    //высокий уровень
													_delay_ms(30);
												}
												PORTB &= ~(1<<5);    //низкий уровень
												i = 0;
												break;
											}
											/*else 
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
											}*/
										//}
//--------------------------------------------------------------------------								
										/*if(scan_key()==12)
										{
											while(scan_key()==12);
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
										}*//*
										_delay_ms(10);
									}
									lcdClear();
									_delay_ms(30);
								}*/
								_delay_ms(30);
							}
						}
//--------------------------------------------------------------------------						
						for (n=12; n<129; n+=4)
						{
							eeprom_busy_wait();
							var = eeprom_read_dword(n);
							if  (Result_Copy  ==  var) 
							{ 
								flag++;
								all_on++;
								eeprom_busy_wait();
								eeprom_write_dword(0, all_on);
								lcdClear();
								_delay_ms(30);
								for(j=0; j<=zt; j++)
								{
									if (j<100)
									{
										PORTB |=(1<<3);    //высокий уровень
									}
									else if (j>=100)
									{
										PORTB &= ~(1<<3);    //низкий уровень
									}									
									lcdGotoXY(1,4); 
									lcdPuts("Unlocked"); 
									//зеленый светодиод
									PORTB |=(1<<5);    //высокий уровень 
									_delay_ms(30);
								}
								PORTB &= ~(1<<3);    //низкий уровень
								PORTB &= ~(1<<5);    //низкий уровень
								break;
							}
						}
//--------------------------------------------------------------------------						
						//if (flag==1)
						//{
							//cycle--;
							memset(Result, 0, sizeof Result);//------------------
							f = -1;//------------------
							r = 0;
							if (flag == 0)
							{
								m = 0;
							}
							else if (flag == 1)
							{
								flag = 0;
							}
						//}
						//memset(Result, 0, sizeof Result);//------------------
						//f = -1;//------------------
						//break;
						lcdClear();
						_delay_ms(30);
					}
					/*else  if (Result[4] == 0) 
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
					}*/
				}
////////////////////////////////////////////////////////////////////////////			
				if(scan_key()==12)
				{
					while(scan_key()==12);
					//_delay_ms(30);
					if (Result[0] != 0)
					{
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
				}
////////////////////////////////////////////////////////////////////////////				
				if (m == ct22)
				{
					memset(Result, 0, sizeof Result);//------------------
					f = -1;//------------------
					r = 0;
				}
////////////////////////////////////////////////////////////////////////////			
				_delay_ms(10);		
			}
		}
		else if (cycle > 0)
		{
			if (cycle == 1)
			{			
//--------------------------------------------------------------------------		
				PORTB &= ~(1<<4);    //низкий уровень
				_delay_ms(30);
//--------------------------------------------------------------------------				
				PORTB &= ~(1<<7);    //низкий уровень
				_delay_ms(10);
//--------------------------------------------------------------------------				
				PORTB |=(1<<6);    //высокий уровень
				_delay_ms(10);
//--------------------------------------------------------------------------				
			}		
			if (cycle == 100)
			{
				cycle = 2;
			}
		}
		cycle++;
	}
}