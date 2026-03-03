#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

const int pirPin = 33;
const int buzzerPin = 14;

Adafruit_SH1107 display = Adafruit_SH1107(128, 128, &Wire, -1);

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  display.begin(0x3c, true);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  
  // PIR sensors need about 30-60 seconds to "warm up"
  display.setCursor(0,0);
  display.println("Warming up...");
  display.display();
  delay(15000); 
}

void loop() {
  int motion = digitalRead(pirPin);

  display.clearDisplay();
  display.setCursor(0, 40);

  if (motion == HIGH) {
    display.println("INTRUDER!");
    digitalWrite(buzzerPin, HIGH);
  } else {
    display.println("SECURE");
    digitalWrite(buzzerPin, LOW);
  }
  
  display.display();
  delay(100);
}