/*
The default setup for the LED and the button to be working.
Debounce is *not* managed at all.
Many configurations for the LED and the button are available.
I implemented 3 of them and then I used the more classical one:
The LED turns ON *while* the button is pressed; OFF otherwise.
*/

#define MODE_TOOGLE 1
#define MODE_HOLD 2
#define MODE_BLINK 3

// Modify this value to change the LED behavior
#define CURRENT_MODE MODE_TOOGLE

const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

// Required for the Toogle mode
int ledState = 0;

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
  handleLED(int mode);
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void handleLED(int mode) {
  switch (mode) {
    case MODE_TOOGLE:
      toogleLED();
      break;
    case MODE_HOLD:
      holdLED();
      break;
    case MODE_BLINK:
      blinkLED();
      break;
  }
}

// Here below are the implementations for the LED
void toogleLED(int buttonState) {
  if (buttonState == HIGH) {
  ledState = !ledState;
  digitalWrite(ledPin, ledState);
  }  

  buttonPressCount++; // Increment the press count
  Serial.println(buttonPressCount);
}

void holdLED(int buttonState) {
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);

    buttonPressCount++; // Increment the press count
    Serial.println(buttonPressCount);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void blinkLED(int buttonState) {
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);

    buttonPressCount++; // Increment the press count
    Serial.println(buttonPressCount);
  }
}

