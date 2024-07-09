#define LED 13

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // Funzione per scrivere la stringa in codice Morse
  morseCode("OASI DI PACE");
  // Attendi un po' prima di ripetere
  delay(10000);
}

void morseCode(String message) {
  for (int i = 0; i < message.length(); i++) {
    char c = toupper(message[i]);
    if (c == ' ') {
      // Spazio tra le parole
      delay(700); 
    } else {
      // Converti il carattere in Morse e invia
      sendMorse(c);
      // Pausa tra le lettere
      delay(300);
    }
  }
}

void sendMorse(char c) {
  switch (c) {
    case 'O': dash(); dash(); dash(); break;
    case 'A': dot(); dash(); break;
    case 'S': dot(); dot(); dot(); break;
    case 'I': dot(); dot(); break;
    case 'D': dash(); dot(); dot(); break;
    case 'P': dot(); dash(); dash(); dot(); break;
    case 'C': dash(); dot(); dash(); dot(); break;
    case 'E': dot(); break;
  }
}

// Funzione per il punto
void dot() {
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
}

// Funzione per la linea
void dash() {
  digitalWrite(LED, HIGH);
  delay(600);
  digitalWrite(LED, LOW);
  delay(200);
}
