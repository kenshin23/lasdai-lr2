/*
 * main.c
 *
 *  Created on: 29/07/2012
 *      Author: jose
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define PUERTODISPOSITIVO "/dev/ttyUSB0"
#define DEBUG

/***********Funiones de comnicacion serial**************/

int abrirPuerto(char * tty){
   int fd;
   struct termios options;
   fd = open(tty, O_RDWR | O_NOCTTY);
   	fcntl(fd, F_SETFL, 0);
	tcgetattr(fd, &options);
	cfsetispeed(&options, B38400);
	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
	fcntl(fd, F_SETFL, FNDELAY);
	return fd;
}

/*******************************************************/

int cerrarPuerto(int fd){
	int respuesta;
	respuesta = close(fd);
	if(respuesta < 0){
		#ifdef DEBUG
			perror("cerrarPuerto: No se puede cerrar el puerto de comunicacion con el dispocitivo\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/*******************************************************/

int escribirDatos(int fd, int nBytes, unsigned char *sbuf){
	int bytes;
	bytes = write(fd, sbuf, nBytes);
	if(bytes < 0){
		#ifdef DEBUG
			perror("escribirDatos: Error no se pudieron escribir los datos\n");
		#endif
		return (-1);
	}else{
		if(bytes != nBytes){
			#ifdef DEBUG
				printf("escribirDatos: Error solo se logor escribir %u bytes de %u bytes \n", bytes , nBytes);
			#endif
			return (-2);
		}
		return (0);
	}
}

/*******************************************************/

int leerDatos(int fd, int nBytes, unsigned char *sbuf){
	int bytes;
	bytes = read(fd, sbuf, nBytes);
	if(bytes < 0){
		#ifdef DEBUG
			perror("leerDatos: Error no se logro leer los datos\n");
		#endif
		return (-1);
	}if(bytes != nBytes){
		#ifdef DEBUG
			printf("leerDatos: Error solo se logro leer %u bytes de %u bytes \n", bytes, nBytes);
		#endif
		return (-2);
	}
	return (0);
}

void disable2(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = 0x00;
	sbuf[1] = 0x38;
	escribirDatos(fd, 2, sbuf);
}

int asignarVelocidad1(int fd, double velocidad){
	static unsigned char sbuf[3];
	sbuf[0] = 0x00;
	sbuf[1] = 0x31;
	sbuf[2] = velocidad;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	printf("escribio: %d \n", escribir);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarVelocidad1: Error al intentar escribir los datos de velocidad 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarVelocidad1: Error la escritura de la velocidad 1 no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
	return (0);
}

int asignarVelocidad2(int fd, double velocidad){
	static unsigned char sbuf[3];
	sbuf[0] = 0x00;
	sbuf[1] = 0x32;
	sbuf[2] = velocidad;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	printf("escribioModifico: %d \n", escribir);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarVelocidad1: Error al intentar escribir los datos de velocidad 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarVelocidad1: Error la escritura de la velocidad 1 no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
	return (0);
}

void get_current_1(int fd){
	static unsigned char sbuf[3];
	sbuf[0] = 0x00;
	sbuf[1] = 0x2C;
	escribirDatos(fd, 2, sbuf);
	usleep(7800);
	leerDatos(fd, 3, sbuf);
	//printf("voltaje %f \n", vol);
	//printf("corriente 1: %f \n", corriente1);
	//printf("corriente 2 %f \n", corriente2);

}

int main(){
	int fd;
	char * tty;
	tty = "/dev/ttyUSB0";
	double velocidad = 170;
	fd = abrirPuerto(tty);
	disable2(fd);
	asignarVelocidad2(fd,velocidad);
	asignarVelocidad1(fd,velocidad);
	usleep(15000000);
	velocidad = 128;
	asignarVelocidad1(fd,velocidad);
	asignarVelocidad2(fd,velocidad);
	cerrarPuerto(fd);
	return 0;
}

