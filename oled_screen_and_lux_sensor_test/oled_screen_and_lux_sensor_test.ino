#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "Adafruit_VEML7700.h"

// OLED Settings
#define i2c_Address 0x3c 
Adafruit_SH1107 display = Adafruit_SH1107(128, 128, &Wire, -1);

// Lux Sensor Settings
Adafruit_VEML7700 veml = Adafruit_VEML7700();

void setup() {
  Serial.begin(115200);

  // Initialize OLED
  if (!display.begin(i2c_Address, true)) {
    Serial.println("OLED not found");
    while (1);
  }
  
  // Initialize Lux Sensor
  if (!veml.begin()) {
    Serial.println("VEML7700 not found");
    while (1);
  }

  // Setup sensor gain/integration time for best results
  veml.setGain(VEML7700_GAIN_1_8);
  veml.setIntegrationTime(VEML7700_IT_100MS);

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setRotation(1); // Set to 1 for your 128x128 screen
}

void loop() {
  float lux = veml.readLux();

  display.clearDisplay();
  
  // Title
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("LUX METER");
  display.drawLine(0, 20, 128, 20, SH110X_WHITE);

  // Big Lux Value
  display.setCursor(0, 45);
  display.setTextSize(3);
  display.print((int)lux);
  
  display.setTextSize(1);
  display.setCursor(0, 80);
  display.println(" Lumens/m2");

  // Visual Light Bar
  int barWidth = map(lux, 0, 1000, 0, 120); // Scale 0-1000 lux to bar width
  display.drawRect(0, 110, 120, 10, SH110X_WHITE);
  display.fillRect(0, 110, barWidth, 10, SH110X_WHITE);

  display.display();
  delay(500);
}