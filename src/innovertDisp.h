// innovertDisp v1.0 library for Arduino.
// 02/11/2019, Arduino IDE v1.8.5, Vladimir Shuvalov (Atreidos)
// Library for connecting to arduino control panel from
// inverter INNOVERT ISD.

// The library does not use hardware SPI, so you can
// use any arduino pins.

// Display connector innovert (if you look at the display itself from the back,
// the key is turned to the left)

// + 5V || + 5V
// GND || GND
// M1SO - P12 |||| A2 - potentiometer
// SS_595 - P8 || P9 - SS_165
// MOS1 - P11 || P13 - CLK



#ifndef innovertDisp_h_
#define innovertDisp_h_

#include <Arduino.h>

class innovertDisp {

  public:
    innovertDisp();
    void init(uint8_t SS_595, uint8_t SS_165, uint8_t POTEN); // Initialization 
    // assignment of pins of latches 595 and 165
    // MOSI / MISO / CLK registers are assigned as the default in SPI on pins 11/12/13, and the analog input    
    // potentiometer in digital form (i.e. 14-19, which corresponds to pins A0-A5)
    void init(uint8_t SS_595, uint8_t SS_165, uint8_t MOSI, uint8_t MISO, uint8_t CLK, uint8_t POTEN);
    // Initialization of assignment of pins of latches (SS) 595 and 165, MOSI / MISO / CLK to any pins of arduino, potentiometer
    uint8_t read(); 
    // returns the byte of the bit mask of the state of the buttons 
    uint16_t innovertDisp::potentiometer(void); 
    // returns the 10 bit value read by the ADC from the potentiometer
    void pool(void); // must constantly spin in the main cycle for correct reading
    // and timely reaction to changing buttons state
    void ShowDigit(uint8_t num, uint8_t digit); // outputs the bit mask of the number to the specified bit 
    // of the seven-segment display
    void dispDigit(uint8_t num, uint8_t digit); // inverted ShowDigit function
    // of the seven-segment display
    void dispInt(uint8_t Disp_data[]); // Displaying four digits to the screen using an array
    void dispInt(uint8_t dig0, uint8_t dig1, uint8_t dig2, uint8_t dig3); // Output 4 digits separately
    void dispByte(uint8_t Disp_data[]); // Outputting four characters using an array of bit masks
    uint8_t but_state = 0;  // The state of the buttons in the form of a bit mask byte, when the button 
    // is pressed 1 is written to the corresponding bit, it is necessary to reset this byte to 0 
    //after processing button states. 
 
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
