const int buttonPin = 2;
const int ledPin = 13;

int buttonState = 0;
int lastButtonState = 0;
int buttonPressCount = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(1200);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Check for state change and count button presses
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttonPressCount++;
    }
    lastButtonState = buttonState;
    Serial.println("----------");
  }

  // Send button state to the serial monitor
  if (buttonState == HIGH) {
    Serial.println("         |\n");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("|         \n");
    digitalWrite(ledPin, LOW);
  }
}
