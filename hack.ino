#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <WiFi.h>
#include "esp_sleep.h"
//#include <DHT.h>
//DHT dht(4, DHT11);
//const char* ssid = "realme 8 5G";
//const char* password = "madhuri123";
volatile bool fireDetected = false;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Not used in some modules

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin(21, 22); 
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   pinMode(GPIO_NUM_13, INPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  display.clearDisplay();
   
   display.display();
//  dht.begin();
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) delay(500);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 1);
   
}
int flag=0;
void loop() {
  
 
 // Serial.println("Going to sleep...");
  esp_light_sleep_start();
  fireDetected = true;

  while (fireDetected) {

    // Turn ON alarm outputs
    if(fireDetected && flag==0){
    //digitalWrite(18, HIGH);
   // digitalWrite(19, HIGH);
    display.clearDisplay();
      display.setTextSize(2);
   display.setTextColor(SSD1306_WHITE);
   display.setCursor(0,0);
    display.println("fire");
    display.display();
    flag++;

    }
    // Continuously monitor fire sensor
    if (digitalRead(27) == LOW) {
     // Serial.println(" Fire cleared");
      fireDetected = false;
      //display.clearDisplay();
      
    }


    delay(1000);   // short, non-dangerous delay
  }

  // ---------- RESET STATE ----------
 digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  display.clearDisplay();
  display.display();
  flag--;

  
 
}
