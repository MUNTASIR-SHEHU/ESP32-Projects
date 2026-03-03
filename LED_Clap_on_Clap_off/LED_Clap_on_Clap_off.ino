const int soundPin = 33;
const int relayPin = 14;

bool lightState = false;       // Keeps track of ON/OFF
unsigned long lastClapTime = 0; // To prevent "double-triggering"
const int delayBetweenClaps = 500; // Half a second "cooldown"

void setup() {
  Serial.begin(115200);
  pinMode(soundPin, INPUT);
  pinMode(relayPin, OUTPUT);
  
  // Start with the light off
  digitalWrite(relayPin, LOW); 
}

void loop() {
  // Read the sound sensor
  int soundDetected = digitalRead(soundPin);

  // If the sensor sees a "LOUD" event (usually LOW for these modules)
  // and enough time has passed since the last clap...
  if (soundDetected == LOW && (millis() - lastClapTime > delayBetweenClaps)) {
    
    lightState = !lightState; // Toggle the state (if true, make false)
    
    if (lightState) {
      digitalWrite(relayPin, HIGH); // Turn Relay ON
      Serial.println("Lights ON");
    } else {
      digitalWrite(relayPin, LOW);  // Turn Relay OFF
      Serial.println("Lights OFF");
    }

    lastClapTime = millis(); // Record the time of this clap
  }
}