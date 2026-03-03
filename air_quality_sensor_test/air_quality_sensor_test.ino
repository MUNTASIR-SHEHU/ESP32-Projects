const int MQ135_PIN = 34; // Analog pin for MQ-135

void setup() {
  Serial.begin(115200);
  // No pinMode needed for analogRead on ESP32
}

void loop() {
  // Read the analog value (0 to 4095 on ESP32)
  int airQualityRaw = analogRead(MQ135_PIN);
  
  // Convert to a percentage for easier reading (optional)
  float percentage = (airQualityRaw / 4095.0) * 100.0;

  Serial.print("Air Quality Raw: ");
  Serial.print(airQualityRaw);
  Serial.print(" | Approx Load: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(2000); // Wait 2 seconds between reads
}