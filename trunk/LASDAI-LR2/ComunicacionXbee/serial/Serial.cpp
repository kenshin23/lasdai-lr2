#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "Serial.h"

Serial::Serial(){
    _serial_fd= -1;
}

int Serial::Open(char *serial_name, speed_t baud) {
	return 0;
}

void Serial::Send(uint8_t *data, int size) {

}

int Serial::Read(uint8_t* data, int size, int timeout_usec) {
	return 0;
}

void Serial::Close() {

}

bool Serial::IOKbHit() {
	return true;
}

bool Serial::IOKbHit(int timeout_ms) {
	return true;
}

uint8_t Serial::IOGetCh() {
	return 0;
}

int Serial::Flush() {
	return 0;
}

