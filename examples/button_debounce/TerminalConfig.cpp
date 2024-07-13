#include "TerminalConfig.h"
#include <termios.h>
#include <unistd.h>

static struct termios orig_termios;

void enable_raw_mode() {
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disable_raw_mode() {
  tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

