#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Encoder Pins
const int clkPin = 32;
const int dtPin = 33;
const int swPin = 14;

int counter = 0;
int lastStateCLK;
unsigned long lastButtonPress = 0;

Adafruit_SH1107 display = Adafruit_SH1107(128, 128, &Wire, -1);

void setup() {
  Serial.begin(115200);
  
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Use internal resistor for the button

  display.begin(0x3c, true);
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(clkPin);
}

void loop() {
  // 1. Check for Rotation
  int currentStateCLK = digitalRead(clkPin);

  if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    // If DT is different than CLK, we are turning Clockwise
    if (digitalRead(dtPin) != currentStateCLK) {
      counter++;
    } else {
      counter--;
    }
    updateDisplay();
  }
  lastStateCLK = currentStateCLK;

  // 2. Check for Button Press (Reset)
  int btnState = digitalRead(swPin);
  if (btnState == LOW && (millis() - lastButtonPress > 50)) {
    counter = 0;
    updateDisplay();
    lastButtonPress = millis();
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println("ENCODER:");
  display.setTextSize(4);
  display.setCursor(20, 50);
  display.println(counter);
  display.display();
}