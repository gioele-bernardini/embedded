#include <iostream>
#include <libserialport.h>
#include <unistd.h>
#include <sys/time.h>
#include <string>

const int N_COLUMNS = 130;
const int N_TRANSITIONS_LINES = 10;

void set_default(int* plot_array, int length) {
  for (int i = 0; i < length; i++) {
    plot_array[i] = 0;
  }
}

void update_forward(int* plot_array, int length) {
  for (int i = 0; i < length - 1; i++) {
    plot_array[i] = plot_array[i + 1];
  }
}

void print_plot(int* plot_array, int length) {
  std::string output;

  for (int i = 0; i < length; i++) {
    output += (plot_array[i] == 1) ? "_" : " ";
  }
  output += "\n";

  for (int j = 0; j < N_TRANSITIONS_LINES; j++) {
    for (int i = 0; i < length - 1; i++) {
      output += (plot_array[i] != plot_array[i + 1]) ? "|" : " ";
    }
    output += "\n";
  }

  for (int i = 0; i < length; i++) {
    output += (plot_array[i] == 0) ? "_" : " ";
  }
  output += "\n";

  std::cout << output;
}

bool read_from_serial(sp_port* port) {
  char c;
  int bytes_read = sp_blocking_read(port, &c, 1, 10);
  return (bytes_read > 0 && c == '1');
}

int main() {
  unsigned press_count = 0;

  sp_port* port;
  sp_return result = sp_get_port_by_name("/dev/ttyACM0", &port);
  if (result != SP_OK) {
    std::cerr << "Error finding serial port\n";
    return 1;
  }

  result = sp_open(port, SP_MODE_READ);
  if (result != SP_OK) {
    std::cerr << "Error opening serial port\n";
    return 1;
  }

  sp_set_baudrate(port, 9600);
  sp_set_bits(port, 8);
  sp_set_parity(port, SP_PARITY_NONE);
  sp_set_stopbits(port, 1);
  sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);

  int plot_array[N_COLUMNS];
  set_default(plot_array, N_COLUMNS);

  timeval start, current;
  gettimeofday(&start, nullptr);

  bool last_button_state = false;
  while (true) {
    bool button_pressed = read_from_serial(port);

    if (button_pressed != last_button_state) {
      press_count++;
      plot_array[N_COLUMNS - 1] = button_pressed ? 1 : 0;
      last_button_state = button_pressed;
    } else {
      plot_array[N_COLUMNS - 1] = 0;
    }

    update_forward(plot_array, N_COLUMNS);

    std::cout << "\033[2J\033[1;1H\n";
    print_plot(plot_array, N_COLUMNS);

    gettimeofday(&current, nullptr);
    long elapsed_seconds = current.tv_sec - start.tv_sec;
    std::cout << "\nElapsed time: " << elapsed_seconds << " seconds\n";

    std::cout.flush();
    usleep(10000);
  }

  sp_close(port);
  sp_free_port(port);

  return 0;
}
