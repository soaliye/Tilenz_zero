#ifndef T_CONFIG_H
#define T_CONFIG_H

#include <Arduino.h>

// --------------| DEVICE INFORMATION
#define DEVICE_NAME     "TILENZ"
#define DEVICE_SLOGAN   "YOUR TIME AUDIT"
#define SYSTEM_PROMPT   "tilenz@zero: "

// --------------| SYSTEM SETTINGS
constexpr uint32_t BAUD_RATE = 115200;

// --------------| PINS
constexpr uint8_t SELECT_PIN = 18;
constexpr uint8_t LEFT_PIN   = 19;
constexpr uint8_t RIGHT_PIN  = 23;
constexpr uint8_t BUZZER_PIN = 13;
constexpr uint8_t LED_PIN    = 2;

constexpr uint8_t RTC_CLK    = 12;
constexpr uint8_t RTC_DATA   = 14;
constexpr uint8_t RTC_RST    = 27;

// --------------| LCD
constexpr uint8_t LCD_ADDR   = 0x27;
constexpr uint8_t LCD_COLS   = 16;
constexpr uint8_t LCD_ROWS   = 2;

#endif
