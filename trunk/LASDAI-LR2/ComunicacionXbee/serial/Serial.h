#ifndef SERIAL_H_
#define SERIAL_H_

#include <termios.h>
#include <inttypes.h>
#include "../../ComunicacionSerial/serial.h"

class Serial {

	private:

    	int _serial_fd;

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
