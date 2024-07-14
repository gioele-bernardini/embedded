const int buttonPin = 2;
const int ledPin = 13;
// increase if output flickers
const unsigned long debounceDelay = 50;

int buttonState = 0;
// the last time the output pin was toggled
unsigned long lastDebounceTime = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  // check if the button state has changed
  if (reading != buttonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
    }
  }

  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("1");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("0");
  }
}

