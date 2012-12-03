/**
 @file percepcion.c
 @brief .
 @date Diciembre, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "percepcion.h"
#include "definicion.h"
#include "../ComunicacionSerial/serial.h"


int iniciarComunicacionSP(int *fd){
	int com;
	com = abrirPuerto(fd,TTY_PERCEPCION,BAUDIOS_PERCEPCION);
	if(com !=  0){
			#ifdef PERCEPCION_DEBUG
				perror("iniciarComunicacionSP: Error al iniciar la comunicación con el Sistema de Percepción.\n");
			#endif
			return (-1);
	}else{
		return (0);
	}
}

int obtenerMedidaSensorUS(int fd, int idSensorUS, int *distanciaUS){
	static unsigned char sbuf[4];
	unsigned short int _distanciaUS;
	int escribir, leer;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_MEDIDA_US;
	sbuf[2] = idSensorUS;
	sbuf[3] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd, 4, sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerMedidaSensorUS: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASO);
		leer = leerDatos(fd,2, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerMedidaSensorUS: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			_distanciaUS = sbuf[0];
			_distanciaUS = (_distanciaUS<<8)+sbuf[1];
			*distanciaUS = (int)_distanciaUS;
			return (0);
		}
	}
}

int obtenerMedidaSensorIR(int idSensorIR){
	return 0;
}

int obtenerMedidaSensorTraseroUS(int angulo){
	return 0;
}

int obtenerBarridoFrontalUS(){
	return 0;
}

int obtenerBarridoFrontalIR(){
	return 0;
}

int obtenerBarridoTraseroUS(){
	return 0;
}

int terminarComunicacionSP(int fd){
	int com;
	com = cerrarPuerto(fd);
	if(com !=  0){
			#ifdef PERCEPCION_DEBUG
				perror("terminarComunicacionSP: Error al terminar la comunicación con el sistema de Percepción.\n");
			#endif
			return (-1);
	}else{
		return (0);
	}
}
