#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// DOIT ESP32 DevKit V1 Pins
#define SDA_PIN 21
#define SCL_PIN 22
#define GAS_PIN  36   // Connected to VP
#define HEAT_PIN 4    // Connected to D4

// BLE Custom UUIDs (Universally Unique Identifiers)
#define SERVICE_UUID        "4FAFC201-1FB5-459E-8FCC-C5C9C331914B"
#define CHARACTERISTIC_UUID "BEA56A26-36F5-474F-94AF-D5C157E2F2B4"

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

// Callback system to track when your phone connects/disconnects
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      // Restart advertising so you can reconnect if it drops
      pServer->getAdvertising()->start();
    }
};

void setup() {
  Serial.begin(115200);

  pinMode(GAS_PIN, INPUT);
  pinMode(HEAT_PIN, INPUT);

  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize SH1106 Screen
  if(!display.begin(0x3C, true)) {
    Serial.println("OLED failed");
    while(1);
  }

  // Set up BLE Local Device Name
  BLEDevice::init("ANAY_BLE_BOX");

  // Create the BLE Server engine
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the wireless Service channel
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the Characteristic channel that sends data strings to the phone
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_NOTIFY 
                    );

  // Add a standard descriptor so phone apps can listen automatically
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the BLE radio service
  pService->start();

  // Start broadcasting the name "ANAY_BLE_BOX" into the air
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("BLE System Ready!");
}

void loop() {
  // Read real data parameters from your hardware pins
  int rawGas = analogRead(GAS_PIN);
  int heatState = digitalRead(HEAT_PIN); 

  // Mocking Temp/Humidity logic since you are migrating to his layout
  int tempValue = (heatState == HIGH) ? 42 : 24; // If heat sensor triggers, show 42°C, else 24°C
  int humidityValue = 55;                        // Baseline room humidity percentage

  // ==========================================
  // 1. PHYSICAL OLED DISPLAY (EXACT SIR LABELS)
  // ==========================================
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);

  // Line 1
  display.setCursor(0, 0);
  display.print("AIR QUALITY INDEX");
  display.drawFastHLine(0, 10, 128, SH110X_WHITE);

  // Line 2
  display.setCursor(0, 16);
  display.print("AQI: ");
  display.print(rawGas);

  // Line 3
  display.setCursor(0, 32);
  display.print("TEMP: ");
  display.print(tempValue);
  display.print(" C");

  // Line 4
  display.setCursor(0, 48);
  display.print("HUMIDITY: ");
  display.print(humidityValue);
  display.print(" %");

  display.display(); // Push layout to the glass layout frame

  // ==========================================
  // 2. WIRELESS BLE DATA STREAM (THE AIR PACKET)
  // ==========================================
  if (deviceConnected) {
    // Build a comma-separated text string to blast to App Inventor
    String dataPacket = String(rawGas) + "," + String(tempValue) + "," + String(humidityValue);
    
    // Cast it into the BLE data box and notify your phone
    pCharacteristic->setValue(dataPacket.c_str());
    pCharacteristic->notify();
    Serial.println("Sent BLE: " + dataPacket);
  }

  delay(500); // Sample and broadcast twice every second
}
