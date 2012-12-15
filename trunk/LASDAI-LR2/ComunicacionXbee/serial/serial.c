/******************************************************************/
/* serial.c   Dr. Juan Gonzalez Gomez. January, 2009              */
/*----------------------------------------------------------------*/
/* Serial communications in Linux                                 */
/*----------------------------------------------------------------*/
/* GPL LICENSE                                                    */
/******************************************************************/

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "serial.h"


//-- Timeout for the select system call, in micro-seconds
#define TIMEOUT_USEC 100000
#define ESC 27
/******************************************************************************/
/* Open the serial port                                                       */
/*----------------------------------------------------------------------------*/
/* INPUT:                                                                     */
/*   -serial_name: Serial device name                                         */
/*   -baud: Serial speed. The constants Bxxxx are used, were xxxx  is the     */ 
/*          speed. They are defined in termios.h. For example: B9600, B19200..*/
/*          For more information type "man termios"                           */
/*                                                                            */
/* RETURNS:                                                                   */
/*   -The Serial device descriptor  (-1 if there is an error)                 */
/******************************************************************************/
int serial_open(char *serial_name, speed_t baud)
{
  struct termios newtermios;
  int fd;

  // Open the serial port
  fd = open(serial_name,O_RDWR | O_NOCTTY | O_NDELAY);

  // Configure the serial port attributes: 
  //   -- No parity
  //   -- 8 data bits
  //   -- other things...
  newtermios.c_cflag= CBAUD | CS8 | CLOCAL | CREAD;
  newtermios.c_iflag=IGNPAR;
  newtermios.c_oflag=0;
  newtermios.c_lflag=0;
  /*newtermios.c_cflag &= ~PARENB;
  newtermios.c_cflag &= ~CSTOPB;
  newtermios.c_cflag &= ~CSIZE;*/
  //newtermios.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  newtermios.c_cc[VMIN]=1;
  newtermios.c_cc[VTIME]=0;

  // Set the speed
  cfsetospeed(&newtermios,baud);
  cfsetispeed(&newtermios,baud);
  
  // flush the input buffer
  if (tcflush(fd,TCIFLUSH)==-1) {
    return -1;
  }

  // flush the output buffer
  if (tcflush(fd,TCOFLUSH)==-1) {
    return -1;
  }

  //-- Configure the serial port now!!
  if (tcsetattr(fd,TCSANOW,&newtermios)==-1) {
    return -1;
  }  

  //-- Return the file descriptor
  return fd;
}

/*****************************************************/
/* Sending a string to the serial port.              */
/*                                                   */
/* INPUT:                                            */
/*   -serial_fd: Serial device descriptor            */
/*   -data:      data string to send                 */
/*   -size:      data string size                    */
/*****************************************************/
void serial_send(int serial_fd, char *data, int size)
{
  write(serial_fd, data, size);
}

/*************************************************************************/
/* Receiving a string from the serial port                               */
/*-----------------------------------------------------------------------*/
/* INPUT                                                                 */
/*   -serial_fd: Serial device descriptor                                */
/*   -size: Maximum data size to receive                                 */ 
/*   -timeout_usec: Timeout time (in micro-secs) for receiving the data  */
/*                                                                       */
/* OUTPUT:                                                               */
/*   -data: The serial data received within the timeout_usec time        */
/*                                                                       */
/* RETURNS:                                                              */
/*   -The number of bytes received.                                      */
/*   -0 if none received. It means a TIMEOUT!                            */
/*************************************************************************/
int serial_read(int serial_fd, char *data, int size, int timeout_usec)
{
  fd_set fds;
  struct timeval timeout;
  int count=0;
  int ret;
  int n;
  
  //-- Wait for the data. A block of size bytes is expected to arrive
  //-- within the timeout_usec time. This block can be received as 
  //-- smaller blocks.
  do {
      //-- Set the fds variable to wait for the serial descriptor
      FD_ZERO(&fds);
      FD_SET (serial_fd, &fds);
    
      //-- Set the timeout in usec.
      timeout.tv_sec = 0;  
      timeout.tv_usec = timeout_usec;

      //-- Wait for the data
      ret=select (FD_SETSIZE,&fds, NULL, NULL,&timeout);
    
    //-- If there are data waiting: read it
      if (ret==1) {
        
        //-- Read the data (n bytes)
        n=read (serial_fd, &data[count], size-count); 
        
        //-- The number of bytes receives is increased in n
        count+=n;
        
        //-- The last byte is always a 0 (for printing the string data)
        data[count]=0;
      }

    //-- Repeat the loop until a data block of size bytes is received or
    //-- a timeout occurs
  } while (count<size && ret==1);

  //-- Return the number of bytes reads. 0 If a timeout has occurred.
  return count;
}



int serial_read_all(int serial_fd, unsigned char *data, int timeout_usec)
{
  fd_set fds;
  struct timeval timeout;
  int count=0;
  int ret;
  int n;

  //-- Wait for the data. A block of size bytes is expected to arrive
  //-- within the timeout_usec time. This block can be received as
  //-- smaller blocks.
  do {
      //-- Set the fds variable to wait for the serial descriptor
      FD_ZERO(&fds);
      FD_SET (serial_fd, &fds);

      //-- Set the timeout in usec.
      timeout.tv_sec = 0;
      timeout.tv_usec = timeout_usec;

      //-- Wait for the data
      ret=select (FD_SETSIZE,&fds, NULL, NULL,&timeout);

    //-- If there are data waiting: read it
      if (ret==1) {

        //-- Read the data (n bytes)
        n=read (serial_fd, &data[count], 1);

        //-- The number of bytes received is increased in n
        count+=n;

        //-- The last byte is always a 0 (for printing the string data)
        data[count]=0;
      }

    //-- Repeat the loop until a data block of size bytes is received or
    //-- a timeout occurs
  } while (ret==1);

  //-- Return the number of bytes reads. 0 If a timeout has occurred.
  return count;
}


/********************************************************************/
/* Close the serial port                                            */
/*------------------------------------------------------------------*/
/* INPUT: :                                                         */
/*   fd: Serial device descriptor                                   */
/********************************************************************/
void serial_close(int fd)
{
  close(fd);
}

/*******************************************************************************/
/*  Check if there are pending characters to be read in the serial buffer      */
/*                                                                             */
/*  RETURNS                                                                    */
/*    0: No pending characters                                                 */
/*    1: The are characters in the buffer ready to be read                     */
/*******************************************************************************/
int serial_io_kbhit(int serial_fd)
{
  int n;
  fd_set rfd;
  struct timeval timeout;

  timeout.tv_sec  = 0;
  timeout.tv_usec = TIMEOUT_USEC;

  FD_ZERO(&rfd);
  FD_SET(serial_fd,&rfd);

  n = select(serial_fd+1,&rfd,NULL,NULL,&timeout);

  return n;
}

/*********************************************************************/
/* Read one character from the serial port. This functions waits     */
/* until a character arrives                                         */
/*********************************************************************/
char serial_io_getch(int serial_fd)
{
  int n;
  char c;

  while (!serial_io_kbhit(serial_fd));

  n = read(serial_fd,&c,1);
  //if (errno==EAGAIN) { continue;}

  return c;
}





