// Continuously prints a single character:
// 'S' if the user is pressing the space key
// ' ' otherwise

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

// Function to enable raw mode for terminal input
void enable_raw_mode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to disable raw mode and restore terminal settings
void disable_raw_mode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to check if a key has been pressed
int kbhit() {
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &fds);
}

int main() {
  enable_raw_mode(); // Enable raw mode for terminal input

  printf("Press 'q' to exit\n");
  while (1) {
    if (kbhit()) {
      int ch = getchar();
      if (ch == 'q') {
        break; // Exit loop if 'q' is pressed
      } else if (ch == ' ') {
        printf("S\n"); // Print 'S' if space is pressed
      } else {
        printf(" \n"); // Print ' ' for any other key
      }
    } else {
      printf(" \n"); // Print ' ' if no key is pressed
    }
    fflush(stdout); // Ensure immediate output
    usleep(50000); // Wait for 50ms to improve responsiveness
  }

  disable_raw_mode(); // Restore terminal settings
  return 0;
}

