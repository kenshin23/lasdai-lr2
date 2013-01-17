/********************************************************************************
* This program is free software; you can redistribute it and/or modify it under *
* the terms of the GNU General Public License as published by the Free Software *
* Foundation; either version 2 of the License, or (at your option) any later 	*
* version. This program is distributed in the hope that it will be useful, but 	*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more *
* details. You should have received a copy of the GNU General Public License 	*
* along with this program; if not, write to the Free Software Foundation, Inc., *
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.						*
* (c) Copyright 2012 José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.	*				*
********************************************************************************/

/**
 @file		serial.c
 @brief		Implementación de funciones para el manejo de puerto serial.
 @date		Junio, 2012
 @author	José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

#include "serial.h"

/*******************************************************/

int abrirPuerto(int *fd, char *tty,  unsigned int baudios){
	int _fd;
	struct termios options;
	_fd = open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
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
		#ifdef SERIAL_DEBUG
		perror("abrirPuerto: No se puede abrir el puerto de comunicación con el dispositivo\n");
	#endif
		return (-1);
   }
}

/*******************************************************/

int escribirDatos(int fd, int nBytes, unsigned char* sbuf){
	int bytes;
	bytes = write(fd, sbuf, nBytes);
	if(bytes < 0){
		#ifdef SERIAL_DEBUG
			perror("escribirDatos: Error no se lograron escribir los datos\n");
		#endif
		return (-1);
	}else{
		if(bytes != nBytes){
			#ifdef SERIAL_DEBUG
				fprintf(stderr,"escribirDatos: Error solo se logro escribir %u bytes de %u bytes\n", bytes , nBytes);
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
		#ifdef SERIAL_DEBUG
			perror("leerDatos: Error no se logro leer los datos\n");
		#endif
		return (-1);
	}if(bytes != nBytes){
		#ifdef SERIAL_DEBUG
			fprintf(stderr,"leerDatos: Error solo se logro leer %u bytes de %u bytes\n", bytes, nBytes);
		#endif
		return (-2);
	}
	return (0);
}

/*******************************************************/

int verificarBufer(int fd, int *nBytes){
	int _nBytes;
	fd_set _fd;
	struct timeval tiempoSalida;
	tiempoSalida.tv_sec  = 0;
	tiempoSalida.tv_usec = TIMEOUT_USEC;
	FD_ZERO(&_fd);
	FD_SET(fd,&_fd);
	_nBytes = select(fd+1,&_fd,NULL,NULL,&tiempoSalida);
	if(_nBytes > 0 ){
		*nBytes = _nBytes;
		return (1);
	}else{
		if(_nBytes == 0){
			 *nBytes = 0;
			 return (0);
		}else{
			#ifdef SERIAL_DEBUG
				perror("verificarBufer: Error no se logro censar si hay datos en el bufer serial.\n");
			#endif
		  *nBytes = 0;
		  return (-1);
		}
	}
}


/*******************************************************/

int cerrarPuerto(int fd){
	int respuesta;
	respuesta = close(fd);
	if(respuesta < 0){
		#ifdef SERIAL_DEBUG
			perror("cerrarPuerto: No se puede cerrar el puerto de comunicación con el dispositivo\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}
