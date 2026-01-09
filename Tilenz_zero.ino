// ----------------| TOOLKIT
#include <Wire.h>
#include <ThreeWire.h>
#include <LiquidCrystal_I2C.h>
#include <RtcDS1302.h>

#define SELECT_PIN 18
#define LEFT_PIN 19
#define RIGHT_PIN 23
#define BUZZER_PIN 13
#define LED_PIN 2

#define RTC_CLK 12
#define RTC_DATA 14
#define RTC_RST 27

const unsigned long baudRate = 115200;
const uint8_t displayAddress = 0x27;
const short width = 16;
const short height = 2;
bool displayFound = false; 

LiquidCrystal_I2C Display(displayAddress, width, height);

ThreeWire thisWire(RTC_DATA, RTC_CLK, RTC_RST);
RtcDS1302<ThreeWire> thisClock(thisWire);
RtcDateTime now;
char dateTimeBuffer[17];
TaskHandle_t DisplayDateTimeHandle = NULL;
TaskHandle_t LEDTaskHandle = NULL;

void show(String main, int colMain, String content, int colContent);

void setup() {
  // put your setup code here, to run once:

  // -----------| SERIAL
  Serial.begin(baudRate);

  // -----------| DISPLAY
  //Wire.beginTransmission(displayAddress);
  //volatile uint8_t status = Wire.endTransmission();
  //displayFound = (status == 0);
  Display.init();
  Display.backlight();
  /*
  if(displayFound){
    Display.init();
    Display.backlight();
  }else{
    while(1);
  }
  */
  pinMode(SELECT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  show("TILENZ V0", 0, "YOUR TIME AUDIT", 0);

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
  Serial.printf("tilenz@zero: SERIAL BAUD RATE = %ul\n", baudRate);
  Serial.printf("tilenz@zero: I2C ADDRESS = 0x%02X\n", displayAddress);
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

void LEDBlink(void *parameters){
  for(;;){
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(200);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(200);
  }
}


void ShowDate(void *parameters){
  for(;;){
    now = thisClock.GetDateTime();
    
    dateTimeBuffer[17]; 
    snprintf(dateTimeBuffer, sizeof(dateTimeBuffer), "%02u/%02u/%04u %02u:%02u", 
            now.Day(), now.Month(), now.Year(), 
            now.Hour(), now.Minute()
            );

    // Display on the second line
    Display.setCursor(0, 1);
    Display.print(dateTimeBuffer);
  }
}

