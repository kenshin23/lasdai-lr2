/*
 * Serial.cpp
 *
 *  Created on: 02/12/2012
 *      Author: julian
 */

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "Serial.h"

extern "C" {
#include "serial.h"
}

Serial::Serial() {
    _serial_fd= -1;
    _buffer = new uint8_t[BUFFER_SIZE];
}

int Serial::Open(char *serial_name, speed_t baud) {
    struct termios newtermios;
    //int _serial_fd;

    // Open the serial port
    _serial_fd = open(serial_name, O_RDWR | O_NOCTTY | O_NDELAY);

    // Configure the serial port attributes:
    //   -- No parity
    //   -- 8 data bits
    //   -- other things...
    newtermios.c_cflag = CBAUD | CS8 | CLOCAL | CREAD;
    newtermios.c_iflag = IGNPAR;
    newtermios.c_oflag = 0;
    newtermios.c_lflag = 0;
    /*newtermios.c_cflag &= ~PARENB;
     newtermios.c_cflag &= ~CSTOPB;
     newtermios.c_cflag &= ~CSIZE;*/
    //newtermios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    newtermios.c_cc[VMIN] = 1;
    newtermios.c_cc[VTIME] = 0;

    // Set the speed
    cfsetospeed(&newtermios, baud);
    cfsetispeed(&newtermios, baud);

    // flush the input buffer
    if (tcflush(_serial_fd, TCIFLUSH) == -1) {
        return -1;
    }

    // flush the output buffer
    if (tcflush(_serial_fd, TCOFLUSH) == -1) {
        return -1;
    }

    //-- Configure the serial port now!!
    if (tcsetattr(_serial_fd, TCSANOW, &newtermios) == -1) {
        return -1;
    }

    //-- Return the file descriptor
    return _serial_fd;
}

void Serial::Send(uint8_t* data, int size) {
    write(_serial_fd, data, size);
}

int Serial::Read(uint8_t* data, int size, int timeout_usec) {

    fd_set fds;
    struct timeval timeout;
    int count = 0;
    int ret;
    int n;

    //-- Wait for the data. A block of size bytes is expected to arrive
    //-- within the timeout_usec time. This block can be received as
    //-- smaller blocks.
    do {
        //-- Set the fds variable to wait for the serial descriptor
        FD_ZERO(&fds);
        FD_SET(_serial_fd, &fds);

        //-- Set the timeout in usec.
        timeout.tv_sec = 0;
        timeout.tv_usec = timeout_usec;

        //-- Wait for the data
        ret = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        //-- If there are data waiting: read it
        if (ret == 1) {

            //-- Read the data (n bytes)
            //n = read(_serial_fd, &data[count], size - count);
            n=read (_serial_fd, &_buffer[count], size-count);

            //-- The number of bytes receives is increased in n
            count += n;

            //-- The last byte is always a 0 (for printing the string data)
            //data[count] = 0;
            _buffer[count] = 0;
        }

        //-- Repeat the loop until a data block of size bytes is received or
        //-- a timeout occurs
    } while (count < size && ret == 1);

    memcpy(data,_buffer,count);

    //-- Return the number of bytes reads. 0 If a timeout has occurred.
    return count;
}

void Serial::Close() {
    close(_serial_fd);
}

/*******************************************************************************/
/*  Check if there are pending characters to be read in the serial buffer      */
/*                                                                             */
/*  RETURNS                                                                    */
/*    0: No pending characters                                                 */
/*    1: The are characters in the buffer ready to be read                     */
/*******************************************************************************/
bool Serial::IOKbHit() {
    int n;
    fd_set rfd;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = TIMEOUT_USEC;

    FD_ZERO(&rfd);
    FD_SET(_serial_fd, &rfd);

    n = select(_serial_fd + 1, &rfd, NULL, NULL, &timeout);
    if (n > 0) {
        return true;
    } else {
        return false;
    }
}

bool Serial::IOKbHit(int timeout_ms) {
    int n;
    fd_set rfd;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = timeout_ms*1000;

    FD_ZERO(&rfd);
    FD_SET(_serial_fd, &rfd);

    n = select(_serial_fd + 1, &rfd, NULL, NULL, &timeout);
    if (n > 0) {
        return true;
    } else {
        return false;
    }
}

/*********************************************************************/
/* Read one character from the serial port. This functions waits     */
/* until a character arrives                                         */
/*********************************************************************/
uint8_t Serial::IOGetCh() {

    int n;
    uint8_t c;

    while (!serial_io_kbhit(_serial_fd));

    n = read(_serial_fd, &c, 1);
    //if (errno==EAGAIN) { continue;}

    return c;
}

int Serial::Flush() {
    // flush the input buffer
    if (tcflush(_serial_fd, TCIFLUSH) == -1) {
        return -1;
    }

    // flush the output buffer
    if (tcflush(_serial_fd, TCOFLUSH) == -1) {
        return -1;
    }

    memset(_buffer, 0, BUFFER_SIZE);

    return 0;
}

