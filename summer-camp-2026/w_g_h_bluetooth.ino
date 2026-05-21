#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <BluetoothSerial.h> // Built-in ESP32 Classic Bluetooth library

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// DOIT ESP32 DevKit V1 I2C Pins
#define SDA_PIN 21
#define SCL_PIN 22

// The Chaos Sensor Pins
#define GAS_PIN  36   // Connected to VP (Flying Fish Analog)
#define HEAT_PIN 4    // Connected to D4 (Digital Heat Sensor)

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
BluetoothSerial SerialBT; // Creates our wireless transmission object

void setup() {
  Serial.begin(115200);

  // Initialize the Bluetooth broadcaster name
  SerialBT.begin("ANAY_ROBOT_BOX"); // This is the name your phone will search for!
  Serial.println("Bluetooth Broadcast Ready!");

  // Set the sensor pins to listen mode
  pinMode(GAS_PIN, INPUT);
  pinMode(HEAT_PIN, INPUT);

  // Initialize I2C paths
  Wire.begin(SDA_PIN, SCL_PIN);

  // Boot the SH1106 Screen
  if(!display.begin(0x3C, true)) {
    Serial.println("OLED failed");
    while(1);
  }
}

void loop() {
  // Read current parameters from your hardware pins
  int gasValue = analogRead(GAS_PIN);
  int heatState = digitalRead(HEAT_PIN); 

  // ==========================================
  // 1. PHYSICAL OLED DISPLAY RENDERING (THE GLASS)
  // ==========================================
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  // Draw Header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SYSTEM: anay [BT]");
  display.drawFastHLine(0, 10, 128, SH110X_WHITE); 

  // Draw Gas Readout
  display.setCursor(0, 16);
  display.print("Gas Signal: ");
  display.setTextSize(2);
  display.setCursor(0, 26);
  display.print(gasValue);

  // Draw Heat Readout
  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Heat Tracker: ");
  if (heatState == HIGH) {
    display.print("HOT!");
  } else {
    display.print("NORMAL");
  }

  display.display(); // Push layout to screen

  // ==========================================
  // 2. BLUETOOTH DATA STREAM (THE AIR PACKET)
  // ==========================================
  // We send data in a flat format: "GAS_VALUE,HEAT_STATUS" ended by a newline
  SerialBT.print(gasValue);
  SerialBT.print(","); // The comma acts as a spacer for App Inventor to cut
  if (heatState == HIGH) {
    SerialBT.println("HOT!");
  } else {
    SerialBT.println("NORMAL");
  }

  delay(500); // Send updates every half-second
}
