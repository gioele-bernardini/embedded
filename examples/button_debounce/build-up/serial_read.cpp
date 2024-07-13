#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main() {
  int serialPort = open("/dev/ttyACM0", O_RDWR);

  if (serialPort < 0) {
    std::cerr << "Error " << errno << " opening /dev/ttyACM0: " << strerror(errno) << std::endl;
    return 1;
  }

  termios tty;
  memset(&tty, 0, sizeof tty);

  if (tcgetattr(serialPort, &tty) != 0) {
    std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
    return 1;
  }

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);

  tty.c_cflag |= (CLOCAL | CREAD);    // Ignore modem controls, enable reading
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;         // 8-bit characters
  tty.c_cflag &= ~PARENB;     // No parity bit
  tty.c_cflag &= ~CSTOPB;     // Only need 1 stop bit
  tty.c_cflag &= ~CRTSCTS;    // No hardware flow control

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~(ECHO | ECHOE | ECHONL | ISIG);    // Disable echo
  tty.c_iflag &= ~(IXON | IXOFF | IXANY);             // No software flow control

  tty.c_oflag &= ~OPOST;      // No special output processing

  if (tcsetattr(serialPort, TCSANOW, &tty) != 0) {
    std::cerr << "Error " << errno << " from tcsetattr: " << strerror(errno) << std::endl;
    return 1;
  }

  char readBuf[256];
  memset(&readBuf, '\0', sizeof(readBuf));

  while (true) {
    int numBytes = read(serialPort, &readBuf, sizeof(readBuf));

    if (numBytes < 0) {
      std::cerr << "Error reading: " << strerror(errno) << std::endl;
      break;
    }

    if (strstr(readBuf, "Button Pressed") != nullptr) {
      std::cout << "Hello, World!" << std::endl;
    }

    memset(&readBuf, '\0', sizeof(readBuf));
  }

  close(serialPort);
  return 0;
}

