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
 @file percepcion.c
 @brief Desarrollo de los métodos para el manejo del sistema de percepción definidos en percepcion.h.
 @date Diciembre, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/

#include "percepcion.h"

/****** Métodos de manipulación del sistema de percepción ******/

int iniciarComunicacionSP(){
	int com;
	printf("llegue aqui3");
	com = abrirPuerto(&fd,TTY_PERCEPCION,BAUDIOS_PERCEPCION);

	if(com !=  0){
			#ifdef PERCEPCION_DEBUG
				perror("iniciarComunicacionSP: Error al iniciar la comunicación con el Sistema de Percepción.\n");
			#endif
			return (-1);
	}else{

		return (0);
	}
}

/**************************************************************************************************/

int obtenerMedidaSensorUS(int idSensorUS, int *distanciaUS){
	static unsigned char sbuf[4];
	unsigned long _distanciaUS;
	int escribir, leer;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_MEDIDA_US;
	sbuf[2] = idSensorUS;
	sbuf[3] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd, 4, sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerMedidaSensorUS: Error al intentar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(500000);
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

/**************************************************************************************************/

int obtenerMedidaSensorIR(int idSensorIR, int *distanciaIR){
	static unsigned char sbuf[4];
	int escribir, leer;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_MEDIDA_IR;
	sbuf[2] = idSensorIR;
	sbuf[3] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd, 4, sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerMedidaSensorIR: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(50000);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerMedidaSensorIR: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*distanciaIR = (int)sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerMedidaSensorTraseroUS(int angulo, int *distanciaUST){
	static unsigned char sbuf[4];
	unsigned long _distanciaUST;
	int escribir, leer;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_MEDIDA_UST;
	sbuf[2] = angulo;
	sbuf[3] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd,4,sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerMedidaSensorTraseroUS: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(300000);
		leer = leerDatos(fd,2, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerMedidaSensorTraseroUS: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			_distanciaUST = sbuf[0];
			_distanciaUST = (_distanciaUST<<8)+sbuf[1];
			*distanciaUST = (int)_distanciaUST;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerBarridoFrontalUS(int *distanciasUS){
	static unsigned char sbuf[12];
	unsigned long _distanciasUS;
	int escribir, leer, i;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_BARRIDO_FRONTAL_US;
	sbuf[2] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd,3,sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerBarridoFrontalUS: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(300000);
		leer = leerDatos(fd,12, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerBarridoFrontalUS: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			for(i = 0; i < 6; ++i ){
				_distanciasUS = sbuf[i*2];
				_distanciasUS = (_distanciasUS<<8)+sbuf[(i*2)+1];
				distanciasUS[i] = (int)_distanciasUS;
			}
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerBarridoFrontalIR(int *distanciasIR){
	static unsigned char sbuf[6];
	int escribir, leer, i;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_BARRIDO_FRONTAL_IR;
	sbuf[3] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerBarridoFrontalIR: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(1500000);
		leer = leerDatos(fd,6, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerBarridoFrontalIR: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			for( i = 0; i < 6; ++i ){
				distanciasIR[i] = (int)sbuf[i];
			}
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerBarridoTraseroUS(int *distanciasUST){
	static unsigned char sbuf[10];
	unsigned long _distanciasUST;
	int escribir, leer, i;
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = OBTENER_BARRIDO_TRASERO;
	sbuf[2] = BYTE_FIN_COMANDO;
	escribir = escribirDatos(fd,3,sbuf);
	if(escribir !=  0){
		#ifdef PERCEPCION_DEBUG
			perror("obtenerBarridoTraseroUS: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(700000);
		leer = leerDatos(fd,10, sbuf);
		if(leer != 0){
			#ifdef PERCEPCION_DEBUG
				perror("obtenerBarridoTraseroUS: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			for ( i = 0; i < 5; ++i ) {
				_distanciasUST = sbuf[i*2];
				_distanciasUST = (_distanciasUST<<8)+sbuf[(i*2)+1];
				distanciasUST[i] = (int)_distanciasUST;
			}
			return (0);
		}
	}
}

/**************************************************************************************************/

int terminarComunicacionSP(){
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
