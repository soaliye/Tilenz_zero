//-----------------| Display.cpp
//
//
//---------------------------------------------------------
#include "Display.h"



void Display::display(uint8_t line, String content, char justify) {
    if(line >= LCD_ROWS) return;

    char lineBuffer[LCD_COLS + 1]; 
    
    // Fill the buffer
    memset(lineBuffer, ' ', LCD_COLS);
    lineBuffer[LCD_COLS] = '\0';

    uint8_t length = content.length();
    if (length > LCD_COLS) length = LCD_COLS; // Truncate if too long

    // Justification
    uint8_t startPos = 0;
    if (justify == 'c') {
        startPos = (LCD_COLS - length) / 2;
    } else if (justify == 'r') {
        startPos = LCD_COLS - length;
    } else {
        startPos = 0; // Left align
    }

    // Copy
    memcpy(lineBuffer + startPos, content.c_str(), length);

    // Printe
    myLCD.setCursor(0, line);
    myLCD.print(lineBuffer); 
}

Display::~Display(){
    // System Prompt
    Serial.print(SYSTEM_PROMPT);
    Serial.println("Display Destroyed!");
}