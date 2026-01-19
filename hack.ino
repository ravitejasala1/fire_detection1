#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "esp_sleep.h"
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
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 1);   
}
int flag=0;
void loop() {
 esp_light_sleep_start();
 fireDetected = true;
 while (fireDetected) {
    if(fireDetected && flag==0){
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("fire");
    display.display();
    flag++;
    }
    if (digitalRead(27) == LOW) {
      fireDetected = false;
  }
    delay(1000);
  }
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  display.clearDisplay();
  display.display();
  flag--;

  
 
}

