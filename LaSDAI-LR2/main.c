/*
 * main.c
 *
 *  Created on: 29/07/2012
 *      Author: jose
 */



int main(){
	int fd;
	char * tty;
	tty = "/dev/ttyUSB0";
	double velocidad = 170;
	fd = abrirPuerto(tty);
	asignarVelocidad1(fd,velocidad);
	asignarVelocidad1(fd,velocidad);
	usleep(15000000);
	velocidad = 128;
	asignarVelocidad1(fd,velocidad);
	asignarVelocidad2(fd,velocidad);
	cerrarPuerto(fd);
	return 0;
}

