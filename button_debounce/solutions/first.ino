const int buttonPin = 2;
const int ledPin = 13;

// variables will change:
int buttonState = 0;          // current state of the button
int lastButtonState = 0;      // previous state of the button
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  int reading = digitalRead(buttonPin);

  // check if the button state has changed
  if (reading != lastButtonState) {
    // reset the debounce timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce delay
    // so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // toggle the LED based on the button state
      if (buttonState == HIGH) {
        digitalWrite(ledPin, HIGH);
        Serial.println("1");
      } else {
        digitalWrite(ledPin, LOW);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
