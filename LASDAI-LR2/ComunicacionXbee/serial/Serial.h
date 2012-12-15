/*
 * Serial.h
 *
 *  Created on: 02/12/2012
 *      Author: julian
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <termios.h>
#include <inttypes.h>

//-- Timeout for the select system call, in micro-seconds
#define TIMEOUT_USEC 100000
#define ESC 27
#define BUFFER_SIZE 404

class Serial {
    int _serial_fd;
    uint8_t* _buffer;

public:
    int Open(char *serial_name, speed_t baud);
    void Send(uint8_t *data, int size);
    int Read(uint8_t *data, int size, int timeout_usec);
    void Close();
    bool IOKbHit();
    bool IOKbHit(int timeout_ms);
    uint8_t IOGetCh();
    int Flush();
    Serial();

};

#endif /* SERIAL_H_ */
