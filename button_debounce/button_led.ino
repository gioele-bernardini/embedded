/*
The default setup for the LED and the button to be working.
Debounce is *not* managed at all.
Many configurations for the LED and the button are available.
Here I used a classical approach:
The LED turns ON *while* the button is pressed; OFF otherwise.
*/

const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Check for state change and count button presses
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPressCount++;
      Serial.println(buttonPressCount);
    }
    lastButtonState = buttonState;
  }

  // Send button state to the serial monitor
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

