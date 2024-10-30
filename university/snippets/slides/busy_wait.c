#define OUT_CHAR 0x1000
#define OUT_STATUS 0x1001

int read(char* location) {
  return *location;
}

void write(char* location, char newval) {
  (*location) = newval;
}

int main() {
  char* my_string = "Hello, World!";
  char* current_char = my_string;


  while (*current_char != '\0') {
    write(OUT_CHAR, *current_char);

    while (read(OUT_STATUS) != 0);
    current_char++;
  }

  return 0;
}

