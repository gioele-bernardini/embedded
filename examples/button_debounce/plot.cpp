#include <iostream>
#include "TerminalConfig.h"
#include <unistd.h>
#include <sys/select.h>

// Function to check if a key has been pressed
bool kbhit() {
  timeval tv{};
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
  return FD_ISSET(STDIN_FILENO, &fds);
}

int main() {
  enable_raw_mode(); // Enable raw mode for terminal input

  std::cout << "Press 'q' to exit\n";
  while (true) {
    if (kbhit()) {
      char ch = getchar();
      if (ch == 'q') {
        break; // Exit loop if 'q' is pressed
      } else if (ch == ' ') {
        std::cout << "S\n"; // Print 'S' if space is pressed
      } else {
        std::cout << " \n"; // Print ' ' for any other key
      }
    } else {
      std::cout << " \n"; // Print ' ' if no key is pressed
    }
    std::cout.flush(); // Ensure immediate output
    usleep(50000); // Wait for 50ms to improve responsiveness
  }

  disable_raw_mode(); // Restore terminal settings
  return 0;
}

