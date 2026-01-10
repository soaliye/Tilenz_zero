//----------------| Display.h
// Creates Display class and function prototypes
// Embeds LCD
//--------------------------------------------------------

#ifndef T_DISPLAY
#define T_DISPLAY

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "../config/Config.h"

class Display{
    private:
        LiquidCrystal_I2C &myLCD;
    public:
        Display(LiquidCrystal_I2C& lcd): myLCD(lcd){}
        void display(uint8_t, String, char);
        void clear();
        ~Display();
};

#endif