#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ESP32 I2C Pins
#define SDA_PIN 21
#define SCL_PIN 22

// The Chaos Sensor Pins
#define GAS_PIN  36   // Connected to VP (Analog input)
#define HEAT_PIN 4    // Connected to D4 (Digital input)

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Set the chaos pins to listen for hardware inputs
  pinMode(GAS_PIN, INPUT);
  pinMode(HEAT_PIN, INPUT);

  // Initialize I2C for ESP32
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize OLED
  if(!display.begin(0x3C, true)) {
    Serial.println("OLED failed");
    while(1);
  }
}

void loop() {
  // 1. Read values from the sensors
  int gasValue = analogRead(GAS_PIN);
  int heatState = digitalRead(HEAT_PIN); // Returns 1 (HIGH) or 0 (LOW)

  // 2. Clear the screen memory
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  // 3. Print your name header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SYSTEM: anay");
  display.drawFastHLine(0, 10, 128, SH110X_WHITE); // Visual divider line

  // 4. Print Gas Level readings
  display.setCursor(0, 16);
  display.print("Gas Signal: ");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(gasValue);

  // 5. Print Heat State at the bottom
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Heat Tracker: ");
  if (heatState == HIGH) {
    display.print("HOT!");
  } else {
    display.print("NORMAL");
  }

  // 6. Force the data onto the glass!
  display.display();
  
  // Wait half a second before looping and updating again
  delay(500); 
}
