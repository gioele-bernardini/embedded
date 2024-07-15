const int buttonPin = 2;
const int ledPin = 13;
// The debounce time in milliseconds to prevent immediate state changes
const unsigned long debounceDelay = 50;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current debounced button state
int lastReading = 0;      // Previous button reading
unsigned long lastDebounceTime = 0; // Last time the button state changed

int ledState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600); // Initialize serial communication at 9600 bps
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Check if the debounce period has not passed
  if ((millis() - lastDebounceTime) < debounceDelay) {
    return; // Skip the rest of the loop during debounce period
  }

  // Check if the button state has changed
  if (reading != lastReading) {
    // Immediate state change
    buttonState = reading;  
    if (buttonState == HIGH) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      buttonPressCount++; // Increment the press count
      Serial.println(buttonPressCount);
    }

    // Start debounce timer to ignore further changes for the debounce period
    lastDebounceTime = millis();
  }

  // Save the current reading for the next iteration
  lastReading = reading;
}

