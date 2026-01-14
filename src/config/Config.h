#ifndef T_CONFIG_H
#define T_CONFIG_H

// --------------| DEVICE INFORMATION
#define DEVICE_NAME     "TILENZ"
#define DEVICE_SLOGAN   "GIVING CONTROL"
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

// --------------| ESP 32 PINS
constexpr uint8_t ESP_PIN4   = 4;
constexpr uint8_t ESP_PIN13  = 13;
constexpr uint8_t ESP_PIN14 = 14;
constexpr uint8_t ESP_PIN16 = 16;
constexpr uint8_t ESP_PIN17 = 17;
constexpr uint8_t ESP_PIN18 = 18;
constexpr uint8_t ESP_PIN19 = 19;
constexpr uint8_t ESP_PIN21 = 21;
constexpr uint8_t ESP_PIN22 = 22;
constexpr uint8_t ESP_PIN23 = 23;
constexpr uint8_t ESP_PIN25 = 25;
constexpr uint8_t ESP_PIN26 = 26;
constexpr uint8_t ESP_PIN27 = 27;
constexpr uint8_t ESP_PIN32 = 32;
constexpr uint8_t ESP_PIN33 = 33;

// ONLY INPUT
constexpr uint8_t ESP_PIN34 = 34;
constexpr uint8_t ESP_PIN35 = 35;
constexpr uint8_t ESP_PIN36 = 36;
constexpr uint8_t ESP_PIN39 = 39;

// --------------| LCD
constexpr uint8_t LCD_ADDR   = 0x27;
constexpr uint8_t LCD_COLS   = 16;
constexpr uint8_t LCD_ROWS   = 2;

#endif
