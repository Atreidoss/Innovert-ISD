// innovertDisp v1.0 библиотека для Arduino.
// 11.02.2019, Arduino IDE v1.8.5, Владимир Шувалов (Atreidos)
// Библиотека для подключения к ардуино панели управления от
// преобразователя частоты INNOVERT ISD.

// Библиотека не использует аппаратный SPI , поэтому можно  
// использовать любые пины ардуино.

//   Разьем дисплея инноверт ( если смотреть на сам дисплей сзади,
//   ключ повернут на лево )

//           +5V   ||  +5V
//           GND   ||  GND
//   M1SO  - P12 ||||  A2  - potentiometer
//  SS_595 - P8    ||  P9  - SS_165
//   MOS1  - P11   ||  P13 - CLK


#include <Arduino.h>
#include "innovertDisp.h"

const static uint8_t numeral[10] =
{
  //ABCDEFGdp
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

innovertDisp::innovertDisp()
{

}

void innovertDisp::init(uint8_t SS_595, uint8_t SS_165, uint8_t POTEN)
{
  _SS_595 = SS_595;
  _SS_165 = SS_165;
  _poten = POTEN;
  _MISO = 12;
  _MOSI = 11;
  _CLK = 13;
  init();
}

void innovertDisp::init(uint8_t SS_595, uint8_t SS_165, uint8_t MOSI, uint8_t MISO, uint8_t CLK, uint8_t POTEN)
{
  _SS_595 = SS_595;
  _SS_165 = SS_165;
  _MISO = MISO;
  _MOSI = MOSI;
  _CLK = CLK;
  _poten = POTEN;
  init();
}

void innovertDisp::init()
{
  pinMode (_CLK, OUTPUT);
  pinMode (_MOSI, OUTPUT);
  pinMode (_MISO, INPUT);
  pinMode (_SS_165, OUTPUT);
  pinMode (_SS_595, OUTPUT);
}

uint8_t innovertDisp::read(void)
{
  digitalWrite(_SS_165, HIGH);
  digitalWrite(_SS_165, LOW);
  return shiftIn(_MISO, _CLK, MSBFIRST);
}

uint16_t innovertDisp::potentiometer(void)
{
return analogRead(_poten);
}

void innovertDisp::pool(void)
{
  uint8_t but = read() << 2;
  if (but)
  {
    but_state = but & (but ^ but_prev);
  }
  but_prev = but;
}

void innovertDisp::write(uint8_t byte1, uint8_t byte2)
{
  shiftOut(_MOSI, _CLK, LSBFIRST, byte2);
  shiftOut(_MOSI, _CLK, MSBFIRST, byte1);
  digitalWrite(_SS_595, HIGH);
  digitalWrite(_SS_595, LOW);
}

void innovertDisp::ShowDigit(uint8_t num, uint8_t digit)
{
  write(num, 0b10000000 >> digit);
}

void innovertDisp::dispDigit(uint8_t num, uint8_t digit)
{
  ShowDigit(num, digit);
}

void innovertDisp::dispInt(uint8_t Disp_data[])
{
  for (uint8_t i = 0; i < 4; i++)
  {
    ShowDigit(numeral[Disp_data[i]], i);
  }
}

void innovertDisp::dispInt(uint8_t dig0, uint8_t dig1, uint8_t dig2, uint8_t dig3)
{
  uint8_t dispArray[] = {dig0, dig1, dig2, dig3};
  dispInt(dispArray);
}

void innovertDisp::dispByte(uint8_t Disp_data[])
{
  for (uint8_t i = 0; i < 4; i++)
  {
    ShowDigit(Disp_data[i], 3 - i);
  }
}
