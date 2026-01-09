// ----------------| TOOLKIT
#include <Wire.h>
#include <ThreeWire.h>
#include <LiquidCrystal_I2C.h>
#include <RtcDS1302.h>
#include "src/config/Config.h"

// ----------------| FUNCTION PROTOTYPES
void show(String main, int colMain, String content, int colContent);

bool displayFound = false; 

// ----------------| HARDWARE OBJECTS
LiquidCrystal_I2C Display(LCD_ADDR, LCD_COLS, LCD_ROWS);
ThreeWire thisWire(RTC_DATA, RTC_CLK, RTC_RST);
RtcDS1302<ThreeWire> thisClock(thisWire);

// ----------------| FreeRTOS TASK HANDLES
TaskHandle_t DisplayDateTimeHandle = NULL;
TaskHandle_t LEDTaskHandle = NULL;


// ----------------| HOLDERS
RtcDateTime now;
char dateTimeBuffer[17];


// ----------------| SETUP
void setup() {
  Serial.begin(BAUD_RATE);
  Display.init();
  Display.backlight();

  pinMode(SELECT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  show(DEVICE_NAME, 0, DEVICE_SLOGAN, 0);

  // Init and Set Date & Time
  thisClock.Begin();

  if (thisClock.GetIsWriteProtected()) {
      Serial.println("RTC was write protected, enabling writing now");
      thisClock.SetIsWriteProtected(false);
  }

  if (!thisClock.GetIsRunning()) {
      Serial.println("RTC was halted! Starting oscillator now.");
      thisClock.SetIsRunning(true);
  }

  RtcDateTime time = RtcDateTime(__DATE__, __TIME__);
  RtcDateTime now_ = thisClock.GetDateTime();
  if (now_ < time) {
      thisClock.SetIsWriteProtected(false);
      thisClock.SetDateTime(time);
      thisClock.SetIsWriteProtected(true);
  }

  // ------------------| SYSTEM LOGS
  delay(500);
  Serial.println("--------------------- SYSTEM LOGS ------------------------");
  Serial.printf("tilenz@zero: SERIAL BAUD RATE = %ul\n", BAUD_RATE);
  Serial.printf("tilenz@zero: I2C ADDRESS = 0x%02X\n", LCD_ADDR);
  Serial.printf("tilenz@zero: DISPLAY FOUND = %s\n", displayFound? "True":"False");
  Serial.println("\n");
  delay(500);

  // ------------------| TASKS
  xTaskCreatePinnedToCore(ShowDate, "Show DateTime", 10000, NULL, 1, &DisplayDateTimeHandle, 1);
  xTaskCreatePinnedToCore(LEDBlink, "LED Blink", 4000, NULL, 1, &LEDTaskHandle, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void tick(){
  tone(BUZZER_PIN, 1000, 20);
}

void show(String main, int colMain, String content, int colContent){
  int tab = 16 - main.length();
  Display.clear();
  Display.setCursor(tab > 0? tab:0, 0);
  Display.print(main);
  Display.setCursor(colContent, 1);
  Display.print(content);
}


void ShowDate(void *parameters) {
  for(;;) {
    now = thisClock.GetDateTime();
    
    snprintf(dateTimeBuffer, sizeof(dateTimeBuffer), "%02u/%02u/%04u %02u:%02u", 
            now.Day(), now.Month(), now.Year(), now.Hour(), now.Minute());

    Display.setCursor(0, 1);
    Display.print(dateTimeBuffer);

    vTaskDelay(pdMS_TO_TICKS(1000)); 
  }
}

void LEDBlink(void *parameters) {
  for(;;) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    vTaskDelay(pdMS_TO_TICKS(200)); 
  }
}
