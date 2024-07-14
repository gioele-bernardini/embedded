const int buttonPin = 2;
const int ledPin = 13;
// The debounce time; increase if the output flickers
const unsigned long debounceDelay = 50;

int buttonPressCount = 0;
int buttonState = 0;
int lastReading = 0;  // This was lastButtonState
// The last time the output pin was toggled
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // Initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();  // Reset debounce timer on state change
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;  // Update button state

      // Toggle the LED based on the button state
      if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);
        buttonPressCount++;
        Serial.println(buttonPressCount);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  }

  // save reading for next interation
  lastReading = reading;
}

