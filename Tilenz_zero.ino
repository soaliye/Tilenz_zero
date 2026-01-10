// ----------------| TOOLKIT
#include <Wire.h>
#include <ThreeWire.h>
#include <LiquidCrystal_I2C.h>
#include <RtcDS1302.h>
#include "src/config/Config.h"
#include "src/display/Display.h"
#include "src/app/App.h"
#include "src/homeapp/HomeApp.h"

// ----------------| FUNCTION PROTOTYPES



// ----------------| HARDWARE OBJECTS
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
ThreeWire thisWire(RTC_DATA, RTC_CLK, RTC_RST);
RtcDS1302<ThreeWire> thisClock(thisWire);

// ----------------| SHARED DATA
RtcDateTime now;
char dateTimeBuffer[17];
String username = "Tilenx";
bool displayFound = false; 

// ----------------| OBJECTS
Display LCDisplay(lcd);

HomeApp *homeApp = new HomeApp(thisClock, username);
App *app = homeApp;

// ----------------| FreeRTOS TASK HANDLES
TaskHandle_t DisplayHandle = NULL;


// ----------------| SETUP
void setup() {
  Serial.begin(BAUD_RATE);
  lcd.init();
  lcd.backlight();

  pinMode(SELECT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // -------------| WAKE-UP SCREEN
  LCDisplay.display(0, DEVICE_NAME, 'c');
  LCDisplay.display(1, DEVICE_SLOGAN, 'c');

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
  xTaskCreatePinnedToCore(DisplayDriver, "Display Driver", 20000, NULL, 1, &DisplayHandle, 1);

}

void loop() {
  // put your main code here, to run repeatedly:
}

void tick(){
  tone(BUZZER_PIN, 1000, 20);
}

void DisplayDriver(void *parameters){
  for(;;){
    LCDisplay.clear();
    LCDisplay.display(0, app->getMain(), 'l');
    LCDisplay.display(1, app->getOption(), 'r');

    vTaskDelay(pdMS_TO_TICKS(200)); 
  }
}
