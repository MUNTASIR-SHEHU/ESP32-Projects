const int laserPin = 12;
const int sensorPin = 34; // Analog pin
const int buzzerPin = 14;

int threshold = 0;

void setup() {
  Serial.begin(115200);
  pinMode(laserPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  digitalWrite(laserPin, HIGH); // Turn on the laser
  
  Serial.println("Aligning Laser... Stand back!");
  delay(2000); // Give yourself time to point the laser at the sensor
  
  // Calibrate: Take the current light reading and set threshold 20% lower
  threshold = analogRead(sensorPin) * 0.8; 
  Serial.print("Threshold set to: ");
  Serial.println(threshold);
}

void loop() {
  int lightLevel = analogRead(sensorPin);

  if (lightLevel < threshold) {
    // THE BEAM IS BROKEN!
    Serial.println("INTRUDER DETECTED!");
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}