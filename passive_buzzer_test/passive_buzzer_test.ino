// Musical notes frequencies
#define NOTE_C4  262
#define NOTE_G4  392
#define NOTE_F4  349
#define NOTE_E4  330
#define NOTE_D4  294
#define NOTE_C5  523
#define NOTE_G5  784

const int buzzerPin = 14;

// The melody: notes followed by duration (4 = quarter note, 8 = eighth)
int melody[] = {
  NOTE_C4, 4, NOTE_G4, 4, NOTE_F4, 8, NOTE_E4, 8, NOTE_D4, 8, NOTE_C5, 4, NOTE_G4, 4
};

void setup() {
  // Attach the buzzer pin to the PWM engine
  ledcAttach(buzzerPin, 2000, 8);
}

void loop() {
  for (int thisNote = 0; thisNote < 14; thisNote += 2) {
    int note = melody[thisNote];
    int duration = 1000 / melody[thisNote + 1];

    ledcWriteTone(buzzerPin, note); // Play the note
    delay(duration);
    
    ledcWriteTone(buzzerPin, 0);    // Brief silence between notes
    delay(duration * 0.3);
  }
  delay(2000); // Wait 2 seconds before playing again
}