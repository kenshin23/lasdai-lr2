/**
 @file		serial.c
 @brief		Implementación de funciones para el manejo de puerto serial.
 @date		Junio, 2012
 @author	José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "definicion.h"
#include "serial.h"

/*******************************************************/

int abrirPuerto(int *fd, char *tty,  unsigned int baudios){
	int _fd;
	struct termios options;
	_fd = open(tty, O_RDWR | O_NOCTTY);
    if (_fd >= 0){
		fcntl(_fd, F_SETFL, 0);
		tcgetattr(_fd, &options);
		cfsetispeed(&options, baudios);
		options.c_cflag |= (CLOCAL | CREAD);
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= CS8;
		tcflush(_fd, TCIFLUSH);
		tcsetattr(_fd, TCSANOW, &options);
		fcntl(_fd, F_SETFL, FNDELAY);
		*fd = _fd;
		return (0);
   }else{
		#ifdef DEBUG
		perror("abrirPuerto: No se puede abrir el puerto de comunicación con el dispositivo\n");
		#endif
		return (-1);
   }
}

/*******************************************************/

int cerrarPuerto(int fd){
	int respuesta;
	respuesta = close(fd);
	if(respuesta < 0){
		#ifdef DEBUG
			perror("cerrarPuerto: No se puede cerrar el puerto de comunicación con el dispositivo\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/*******************************************************/

int escribirDatos(int fd, int nBytes, unsigned char* sbuf){
	int bytes;
	bytes = write(fd, sbuf, nBytes);
	if(bytes < 0){
		#ifdef DEBUG
			perror("escribirDatos: Error no se lograron escribir los datos\n");
		#endif
		return (-1);
	}else{
		if(bytes != nBytes){
			#ifdef DEBUG
				printf("escribirDatos: Error solo se logro escribir %u bytes de %u bytes\n", bytes , nBytes);
			#endif
			return (-2);
		}
		return (0);
	}
}

/*******************************************************/

int leerDatos(int fd, int nBytes, unsigned char* sbuf){
	int bytes;
	bytes = read(fd, sbuf, nBytes);
	if(bytes < 0){
		#ifdef DEBUG
			perror("leerDatos: Error no se logro leer los datos\n");
		#endif
		return (-1);
	}if(bytes != nBytes){
		#ifdef DEBUG
			printf("leerDatos: Error solo se logro leer %u bytes de %u bytes\n", bytes, nBytes);
		#endif
		return (-2);
	}
	return (0);
}
