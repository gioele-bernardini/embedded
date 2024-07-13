#include <iostream>
#include "TerminalConfig.h"
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#define N_COLUMNS 130
#define N_TRANSITIONS_LINES 10

// The following functions might have been implemented
// without the length of the array as a parameter,
// as that is a global variabile and could be easily accessed.
// I am nevertheless implementing them this way just for good practice

// Function to initialize all the array elements to 0
void set_default(int* plot_array, int length) {
  for (int i = 0; i < length; i++)
    plot_array[i] = 0;
}

// Function to update the array by shifting elements forward
void update_forward(int* plot_array, int length) {
  for (int i = 0; i < length - 1; i++)
    plot_array[i] = plot_array[i + 1];
}

void print_plot(int* plot_array, int length) {
  std::string output;
  int i;

  for (i = 0; i < length; i++) {
    if (plot_array[i] == 1)
      output += "_";
    else
      output += " ";
  }
  output += "\n";

  for (int j = 0; j < N_TRANSITIONS_LINES; j++) {
    for (i = 0; i < length - 1; i++) {
      if (plot_array[i] != plot_array[i + 1])
        output += "|";
      else
        output += " ";
    }
    output += "\n";
  }

  for (i = 0; i < length; i++) {
    if (plot_array[i] == 0)
      output += "_";
    else
      output += " ";
  }
  output += "\n";

  std::cout << output;
}

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
  // I am not using it for this Poc. Might come in handy later
  unsigned press_count = 0;  

  enable_raw_mode(); // Enable raw mode for terminal input

  // Disable synchronization between C and C++ I/O
  std::ios_base::sync_with_stdio(false);

  int plot_array[N_COLUMNS];
  set_default(plot_array, N_COLUMNS);

  timeval start, current;
  gettimeofday(&start, nullptr);

  while (true) {
    if (kbhit()) {
      char ch = getchar();
      if (ch == 'q') {
        break; // Exit loop if 'q' is pressed
      } else if (ch == ' ') {
        press_count++;
        plot_array[N_COLUMNS - 1] = 1;
      } else {
        plot_array[N_COLUMNS - 1] = 0;
      }
    } else {
      plot_array[N_COLUMNS - 1] = 0;
    }

    update_forward(plot_array, N_COLUMNS);

    // Use ANSI escape codes to clear the screen and move the cursor to the top-left corner
    // Faster than system("clear")
    std::cout << "\033[2J\033[1;1H\n";

    // std::cout << "Press 'q' to exit\n";
    print_plot(plot_array, N_COLUMNS);

    gettimeofday(&current, nullptr);
    long elapsed_seconds = current.tv_sec - start.tv_sec;
    std::cout << "\nElapsed time: " << elapsed_seconds << " seconds\n";

    std::cout.flush(); // Ensure immediate output

    usleep(50000); // Wait for 50ms to improve responsiveness
  }

  disable_raw_mode(); // Restore terminal settings
  return 0;
}

