#include "config.h"

// 123.4
// numbers[0] = 123
// numbers[1] = 4
inline void explodeDoubleNumber(int* numbers, double flt) {
  numbers[0] = abs((int) flt);
  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
}

inline void printTemp(double d) {
  char text[17] = "T = ";
  int fs[2];
  char num[5];
  
  explodeDoubleNumber(fs, d);
  if (d < 0) {
    strcat(text, "-");
  }
  itoa(fs[0], num, 10);
  strcat(text, num);
  strcat(text, ".");
  itoa(fs[1], num, 10);
  strcat(text, num);
  strcat(text, "'C");
  lcdClear();
  lcdGotoXY(0, 0);
  lcdPuts(text);
}

double getTemp(void) {
  uint8_t temperatureL;
  uint8_t temperatureH;
  double retd = 0;
  
  skipRom();
  writeByte(CMD_CONVERTTEMP);
  
  _delay_ms(750);
  
  skipRom();
  writeByte(CMD_RSCRATCHPAD);
  
  temperatureL = readByte();
  temperatureH = readByte();
  
  retd = ((temperatureH << 8) + temperatureL) * 0.0625;
  
  return retd;
}