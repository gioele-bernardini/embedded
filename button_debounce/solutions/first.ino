const int buttonPin = 2;
const int ledPin = 13;
// The debounce time; increase if the output flickers
const unsigned long debounceDelay = 50;

int buttonState = 0;
int lastButtonState = 0;
// The last time the output pin was toggled
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
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

  // Save the reading. Next time through the loop, 
  // it'll be the lastButtonState:
  lastButtonState = reading;
}

