/*
When a new button state is detected, a debounce timer is started.
The new state must remain stable for the duration of the timer to be considered valid.
If the state remains unchanged past the debounce period, buttonState is updated.
If buttonState transitions from LOW to HIGH, it is considered a button press, and the press count is incremented.
*/

const int buttonPin = 2;
const int ledPin = 13;
// The debounce time in milliseconds to ensure stable button reading
const unsigned long debounceDelay = 50;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current debounced button state
int lastReading = 0;      // Previous button reading
unsigned long lastDebounceTime = 0; // Last time the button state changed

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();  // Reset debounce timer on state change
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the debounce period has passed, update buttonState if necessary
    if (reading != buttonState) {
      buttonState = reading;  // Update button state

      // Handle the button press
      if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);
        buttonPressCount++; // Increment the press count
        Serial.println(buttonPressCount);
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  }

  // Save the current reading for the next iteration
  lastReading = reading;
}

