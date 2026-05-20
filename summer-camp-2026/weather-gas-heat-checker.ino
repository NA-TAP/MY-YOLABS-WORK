#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 
#define SCREEN_ADDRESS 0x3C 

// Define the analog pin used for power
#define POWER_PIN_A3 A3

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2       
#define DHTTYPE DHT11  
#define BUZZER_PIN 8   

const float tempThreshold = 45.0; 
bool alarmTriggered = false; 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // CRITICAL: Set up Analog Pin A3 to output 5V power immediately
  pinMode(POWER_PIN_A3, OUTPUT);
  digitalWrite(POWER_PIN_A3, HIGH);
  
  // Brief delay to let the OLED power up before initializing it
  delay(100); 

  Serial.begin(9600);
  dht.begin();
  pinMode(BUZZER_PIN, OUTPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  delay(2000); 

  float t = dht.readTemperature();

  if (isnan(t)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("Sensor Error!");
    display.display();
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("TEMP MONITOR");
  
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(t, 1);
  display.print(" C");

  display.setTextSize(1);
  display.setCursor(0, 50);
  if(alarmTriggered) {
    display.println("STATUS: LACKING COOLDOWN");
  } else {
    display.println("STATUS: SYSTEM ARMED");
  }
  display.display();

  if (t > tempThreshold && !alarmTriggered) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("⚠️ OVERHEAT");
    display.display();
    
    digitalWrite(BUZZER_PIN, HIGH); 
    delay(2000);                    
    digitalWrite(BUZZER_PIN, LOW);  
    
    alarmTriggered = true;          
  } 
  
  else if (t <= tempThreshold && alarmTriggered) {
    alarmTriggered = false;         
  }
}
