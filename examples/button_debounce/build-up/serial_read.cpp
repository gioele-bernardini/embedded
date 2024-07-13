// g++ serial_read.cpp -o serial_read -lserialport

#include <iostream>
#include <unistd.h>
#include <libserialport.h>
#include <cstring>

void configure_port(sp_port* port) {
  sp_set_baudrate(port, 9600);
  sp_set_bits(port, 8);
  sp_set_parity(port, SP_PARITY_NONE);
  sp_set_stopbits(port, 1);
  sp_set_flowcontrol(port, SP_FLOWCONTROL_NONE);
}

int main() {
  sp_port* port;
  sp_return result = sp_get_port_by_name("/dev/ttyACM0", &port); // Cambia con la tua porta seriale
  if (result != SP_OK) {
    std::cerr << "Error finding serial port\n";
    return 1;
  }

  result = sp_open(port, SP_MODE_READ);
  if (result != SP_OK) {
    std::cerr << "Error opening serial port\n";
    return 1;
  }

  configure_port(port);

  char readBuf[256];
  while (true) {
    memset(&readBuf, '\0', sizeof(readBuf));
    int numBytes = sp_nonblocking_read(port, readBuf, sizeof(readBuf) - 1);

    if (numBytes < 0) {
      std::cerr << "Error reading: " << sp_last_error_message() << std::endl;
      sp_free_error_message(sp_last_error_message());
      break;
    }

    if (strstr(readBuf, "1") != nullptr) {
      std::cout << "Button pressed" << std::endl;
    }

    usleep(100000); // Sleep for 100 ms to avoid busy-waiting
  }

  sp_close(port);
  sp_free_port(port);
  return 0;
}

