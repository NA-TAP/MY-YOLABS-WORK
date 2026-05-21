#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// DOIT ESP32 Hardware I2C Pins
#define SDA_PIN 21
#define SCL_PIN 22

// Your Chaos Input Pins
#define GAS_PIN  36   // Connected to VP (Flying Fish Analog)
#define HEAT_PIN 4    // Connected to D4 (Digital Heat Sensor)

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Set up the ears of the ESP32 to listen to the sensors
  pinMode(GAS_PIN, INPUT);
  pinMode(HEAT_PIN, INPUT);

  // Start the communication paths
  Wire.begin(SDA_PIN, SCL_PIN);

  // Boot up the SH1106 screen
  if(!display.begin(0x3C, true)) {
    Serial.println("OLED failed");
    while(1);
  }
}

void loop() {
  // 1. Read values from the hardware pins
  int gasValue = analogRead(GAS_PIN);
  int heatState = digitalRead(HEAT_PIN); 

  // 2. Wipe the old text away
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  // Row 1: Your Name Header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SYSTEM: anay");
  display.drawFastHLine(0, 10, 128, SH110X_WHITE); 

  // Row 2: Flying Fish Gas Readings
  display.setCursor(0, 16);
  display.print("Gas Signal: ");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(gasValue);

  // Row 3: Heat Tracking Status
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Heat Tracker: ");
  if (heatState == HIGH) {
    display.print("HOT!");
  } else {
    display.print("NORMAL");
  }

  // 3. Force the data onto the glass!
  display.display();
  
  // Wait half a second before reading the pins again
  delay(500); 
}
