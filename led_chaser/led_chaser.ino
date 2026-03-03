// A list (array) of the pins we connected our LEDs to
int ledPins[] = {13, 12, 27, 33, 15, 32, 14};
int pinCount = 7; // Total number of LEDs

void setup() {
  // Use a 'for loop' to set all pins as OUTPUT at once
  for (int i = 0; i < pinCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // 1. Move the light from left to right
  for (int i = 0; i < pinCount; i++) {
    digitalWrite(ledPins[i], HIGH); // Turn LED on
    delay(100);                    // Wait 0.1 seconds
    digitalWrite(ledPins[i], LOW);  // Turn LED off
  }

  // 2. Move the light from right to left
  for (int i = pinCount - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH); 
    delay(100);
    digitalWrite(ledPins[i], LOW);
  }
}