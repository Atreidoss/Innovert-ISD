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


#ifndef innovertDisp_h_
#define innovertDisp_h_

#include <Arduino.h>

class innovertDisp {

  public:
    innovertDisp();
    void init(uint8_t SS_595, uint8_t SS_165, uint8_t POTEN); // Инициализация назначение пинов защелок 595 и 165 
    // регистров MOSI/MISO/CLK назначаются как по умолчанию в SPI на пины 11/12/13, и аналоговый вход 
    // потенциометра в цифровом виде ( т.е. 14-19 , что соответствует выводам А0-А5 )
    void init(uint8_t SS_595, uint8_t SS_165, uint8_t MOSI, uint8_t MISO, uint8_t CLK, uint8_t POTEN); // Инициализация 
    // назначение пинов защелок (SS) 595 и 165, MOSI/MISO/CLK на любые пины ардуино, потенциометр
    uint8_t read(); 
    // возвращает байт битовой маски состояния кнопок 
    uint16_t innovertDisp::potentiometer(void); 
    // возвращает 10 битное значение считанное АЦП с потенциометра
    void pool(void); // должен постоянно крутиться в основном цилке, что бы происходило коректное чтение
    // и своевременаня реакция на изменение кнопок
    void ShowDigit(uint8_t num, uint8_t digit); // выводит битовую маску числа в указанный разряд
    // семисегментного дисплея
    void dispDigit(uint8_t num, uint8_t digit); // инвертированная функция ShowDigit
    // семисегментного дисплея
    void dispInt(uint8_t Disp_data[]); // Вывод 4х цифр на экран, с помощью массива
    void dispInt(uint8_t dig0, uint8_t dig1, uint8_t dig2, uint8_t dig3); // Вывод 4х цифр отдельно 
    // прописанных
    void dispByte(uint8_t Disp_data[]); // Вывод 4х знаков с помощью массива битовых масок
    uint8_t but_state = 0;  // Состояние кнопок в виде байта битовой маски, при нажатии кнопки 
    // в соответсвующий бит записывается 1, необходимо сбрасывать этот байт в 0 после обработки
    // состояния кнопок.
 
  private:
    void init();
    void write(uint8_t byte1, uint8_t byte2);
    uint8_t _SS_595;
    uint8_t _SS_165;
    uint8_t _MISO;
    uint8_t _MOSI;
    uint8_t _CLK;
    uint8_t _poten;
    uint8_t but_prev = 0;
};

#define _A 0b01110111
#define _B 0b01111111
#define _C 0b00111001
#define _D 0b00111111
#define _E 0b01111001
#define _F 0b01110001
#define _G 0b00111101
#define _H 0b01110110
#define _I 0b00110000
#define _J 0b00011110
#define _L 0b00111000
#define _O 0b00111111
#define _P 0b01110011
#define _S 0b01101101
#define _U 0b00111110
#define _b 0b01111100
#define _c 0b01011000
#define _d 0b01011110
#define _e 0b01111011
#define _f 0b01110001
#define _h 0b01110100
#define _i 0b00000100
#define _j 0b00001100
#define _l 0b00000110
#define _n 0b01010100
#define _o 0b01011100
#define _q 0b01100111
#define _r 0b01010000
#define _t 0b01111000
#define _u 0b00011100
#define _y 0b01101110

#define _0 0b00111111
#define _1 0b00000110
#define _2 0b01011011
#define _3 0b01001111
#define _4 0b01100110
#define _5 0b01101101
#define _6 0b01111101
#define _7 0b00000111
#define _8 0b01111111
#define _9 0b01101111

#define _dot   0b10000000
#define _slash 0b00001000
#define _empty 0b00000000

#endif
