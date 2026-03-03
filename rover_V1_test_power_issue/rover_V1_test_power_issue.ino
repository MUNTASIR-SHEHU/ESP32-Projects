#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// --- PIN DEFINITIONS ---
// L298N Motor Pins
const int enA = 13;
const int in1 = 12;
const int in2 = 27;

// Joystick Pins
const int joyY = 34;      // Vertical Axis (Analog)
const int joyButton = 26; // Joystick SW Pin (Digital A0)

// Buzzer Pin
const int buzzerPin = 14;

// --- OLED SETTINGS ---
#define i2c_Address 0x3c
Adafruit_SH1107 display = Adafruit_SH1107(128, 128, &Wire, -1);

// --- PWM SETTINGS ---
const int freq = 100;
const int res = 8;

void setup() {
  Serial.begin(115200);

  // Initialize Motor Pins
  ledcAttach(enA, freq, res);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Initialize Buzzer & Button
  pinMode(buzzerPin, OUTPUT);
  pinMode(joyButton, INPUT_PULLUP);

  // Initialize OLED
  if (!display.begin(i2c_Address, true)) {
    Serial.println("OLED failed!");
  }
  display.clearDisplay();
  display.setRotation(1);
}

void loop() {
  // 1. READ INPUTS
  int yRaw = analogRead(joyY);
  bool buttonPressed = (digitalRead(joyButton) == LOW);

  // 2. LOGIC: Calculate Speed & Direction
  // Map 0-4095 to -255 to 255
  int speed = map(yRaw, 400, 3700, -255, 255); 
  
  // Deadzone to prevent "beeping" or crawling when idle
  if (abs(speed) < 100) speed = 0;

  // 3. ACTUATORS: Drive Motors
  if (speed > 0) { // Forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    ledcWrite(enA, speed);
  } 
  else if (speed < 0) { // Backward
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    ledcWrite(enA, abs(speed));
  } 
  else { // Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    ledcWrite(enA, 0);
  }

  // 4. ACTUATORS: Buzzer Logic
  if (buttonPressed) {
    digitalWrite(buzzerPin, HIGH); // Manual Horn
  } 
  else if (speed < 0) {
    // Pulsing Reverse Alarm (No delay used!)
    digitalWrite(buzzerPin, (millis() % 500 < 250)); 
  } 
  else {
    digitalWrite(buzzerPin, LOW);
  }

  // 5. DASHBOARD: Update OLED
  updateDashboard(speed, buttonPressed);
}

// Helper function to keep loop() clean
void updateDashboard(int s, bool b) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("ROVER V1");
  display.drawLine(0, 18, 128, 18, SH110X_WHITE);

  display.setCursor(0, 30);
  display.setTextSize(1);
  display.print("THROTTLE: ");
  display.setTextSize(2);
  display.println((int)s); // Use (int) to keep it clean

  display.setCursor(0, 70);
  display.setTextSize(1);
  display.print("STATUS: ");
  if (s > 0) display.println("FORWARD");
  else if (s < 0) display.println("REVERSE");
  else display.println("IDLE");

  if (b) {
    display.fillRect(0, 100, 128, 20, SH110X_WHITE);
    display.setTextColor(SH110X_BLACK);
    display.setCursor(40, 105);
    display.println("HORN");
    display.setTextColor(SH110X_WHITE);
  }

  display.display();
}