#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ESP32 I2C Pins
#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {

  Serial.begin(115200);

  // Initialize I2C for ESP32
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if(!display.begin(0x3C, true)) {

    Serial.println("OLED failed");

    while(1);
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(10, 20);
  display.println("anay");

  display.display();
}

void loop() {

}