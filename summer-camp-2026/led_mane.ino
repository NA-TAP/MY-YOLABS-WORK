#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     
#define SCREEN_HEIGHT 64     
#define OLED_RESET    -1     
#define SCREEN_ADDRESS 0x3C  // Very common default screen address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Automatically targets D21 (SDA) and D22 (SCL/SCK)
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED failed! Check wires on D21 and D22."));
    for(;;); 
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2); // Thick, bold, and easy-to-read font size
  
  // Center your name on the layout
  display.setCursor(15, 25); 
  
  // Put your real name inside the quotes right here:
  display.println("YOUR NAME"); 

  // Push data to the physical screen pixels
  display.display(); 
}

void loop() {
  // Empty loop so your name just stays up on the panel!
}

