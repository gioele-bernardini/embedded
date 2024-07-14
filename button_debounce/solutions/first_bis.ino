/*
The considerations are the same ones as on the first solution.
Here, a Toogle is implemented to make the button act like a switch. 
Once pressed and the LED will always be ON, until the button won't be pressed once again.
*/

const int buttonPin = 2;
const int ledPin = 13;
// The debounce time in milliseconds to ensure stable button reading
const unsigned long debounceDelay = 50;

int buttonPressCount = 0; // Counter for button presses
int buttonState = 0;      // Current debounced button state
int lastReading = 0;      // Previous button reading
unsigned long lastDebounceTime = 0; // Last time the button state changed

// A toggle for the LED to keep it on and off, 
// making the button act like a switch
int ledState = 0;

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
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
        
        buttonPressCount++; // Increment the press count
        Serial.println(buttonPressCount);
      }
    }
  }

  // Save the current reading for the next iteration
  lastReading = reading;
}

