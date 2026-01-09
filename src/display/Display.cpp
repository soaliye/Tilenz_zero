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
    uint8_t tab = (LCD_COLS - content.length()) / 2;

    // Justify
    if(justify == 'c'){
        myLCD.setCursor(tab, line);
    }else if(justify == 'l'){
        myLCD.setCursor(LCD_COLS - content.length(), line);
    }else{
        myLCD.setCursor(0, line);
    }

    // Print
    myLCD.print(content);
}

Display::~Display(){
    // System Prompt
    Serial.print(SYSTEM_PROMPT);
    Serial.println("Display Destroyed!");
}