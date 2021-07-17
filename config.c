#include "config.h"

// 123.4
// numbers[0] = 123
// numbers[1] = 4
inline void explodeDoubleNumber(int* numbers, double flt) {
  numbers[0] = abs((int) flt);
  numbers[1] = abs((int) ((flt - ((int) flt)) * 10));
}

//inline void printTemp(double d, char text) {
char printTemp(double d, uint8_t i) {
  
  char text[12] = "T";
  int fs[2];
  char num[5];
  
  itoa(i, num, 10);
  strcat(text, num);
  strcat(text, "=");
  
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
  return text;
  //lcdClear();
  //lcdGotoXY(0, 7);
  //lcdPuts(text);
}

double getTemp(uint64_t ds18b20s) {
  uint8_t temperatureL;
  uint8_t temperatureH;
  double retd = 0;


  setDevice(ds18b20s);
  writeByte(CMD_CONVERTTEMP);

  _delay_ms(750);

  setDevice(ds18b20s);
  writeByte(CMD_RSCRATCHPAD);

  temperatureL = readByte();
  temperatureH = readByte();

  retd = ((temperatureH << 8) + temperatureL) * 0.0625;

  return retd;
}