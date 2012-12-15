/******************************************************************/
/* serial.h    Dr. Juan Gonzalez Gomez.    January, 2009          */
/*----------------------------------------------------------------*/
/* Serial communications in Linux                                 */
/*----------------------------------------------------------------*/
/* GPL LICENSE                                                    */
/******************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

#include <termios.h>

/*--------------------------*/
/* FUNCTION PROTOTYPES      */
/*--------------------------*/

int  serial_open(char *serial_name, speed_t baud);

void serial_send(int serial_fd, char *data, int size);

int  serial_read(int serial_fd, char *data, int size, int timeout_usec);

int serial_read_all(int serial_fd, unsigned char *data, int timeout_usec);

void serial_close(int fd);

int  serial_io_kbhit(int serial_fd);

char serial_io_getch(int serial_fd);

#endif  
