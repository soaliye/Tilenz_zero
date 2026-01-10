//-----------------| Display.cpp
//
//
//---------------------------------------------------------
#include "Display.h"


void Display::display(uint8_t line, String content, char justify){
    // Check for legality
    if(line >= LCD_ROWS || line < 0){
        // System Prompt
        Serial.print(SYSTEM_PROMPT);
        Serial.println("Can't display on this line.");
        return;
    }

    // Fitting
    uint8_t length = content.length();
    uint8_t tab = (LCD_COLS - length) / 2;

    // Justify
    if(justify == 'c' && length <= LCD_COLS){
        myLCD.setCursor(tab, line);
    }else if(justify == 'l' && length <= LCD_COLS){
        myLCD.setCursor(LCD_COLS - length, line);
    }else{
        myLCD.setCursor(0, line);
    }

    // Print
    myLCD.print(content);
}

void Display::clear(){
    myLCD.clear();
}

Display::~Display(){
    // System Prompt
    Serial.print(SYSTEM_PROMPT);
    Serial.println("Display Destroyed!");
}