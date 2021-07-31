#include "config.h"

// 123.4
// numbers[0] = 123
// numbers[1] = 4
inline void explodeDoubleNumber(int* numbers, double flt) {
  numbers[0] = abs((int) flt);
  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
}

double getTemp(uint64_t ds18b20s) {
  uint8_t temperatureL;
  uint8_t temperatureH;
  double retd = 0;
  
  //unsigned short tp; // объявляем переменную для цикла
  
  //skipRom();
  setDevice(ds18b20s);
  writeByte(CMD_CONVERTTEMP);
  
  _delay_ms(750);
  /*for(tp=0; tp<25; tp++)
  {
	 _delay_ms(30);
  }*/
  
  //skipRom();
  setDevice(ds18b20s);
  writeByte(CMD_RSCRATCHPAD);
  
  temperatureL = readByte();
  temperatureH = readByte();
  
  retd = ((temperatureH << 8) + temperatureL) * 0.0625;
  
  return retd;
}