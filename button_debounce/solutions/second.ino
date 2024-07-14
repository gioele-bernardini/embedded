const int buttonPin = 2;
const int ledPin = 13;
// Increase if output flickers
const unsigned long debounceDelay = 50;

int buttonState = LOW;
int lastButtonState = LOW;
// The last time the output pin was toggled
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

  //  Serial.print("Reading: ");
  //  Serial.println(reading);

  if (reading != lastButtonState) {
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

  lastButtonState = reading;
}
