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
 @file comandos.c
 @brief Implementación de las funciones declaradas comandos.h, para el manejo de los comandos enviados al servidor socket.
 @date Diciembre, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/

#include "comandos.h"

/****** Funciones  para el manejo de los comandos ******/

int inicializarRobot(){
	int error;
	error = inicializarMovilidad();
	error = iniciarComunicacionSP();
	if(error == 0){
		return (0);
	}else{
		#ifdef COMANDO_DEBUG
			perror("incializarRobot: Error No se lograron inicializar todos los subsistemas de la plataforma.");
		#endif
		return (-1);
	}
}

/*******************************************************/

int destruirRobot(){
	int error;
	error = terminarMovilidad();
	error = terminarComunicacionSP();
	if(error == 0){
		return (0);
	}else{
		#ifdef COMANDO_DEBUG
			perror("destruirRobot: Error al desactivar el robot.");
		#endif
		return (-1);
	}
}

/*******************************************************/

int comandos(int fdCliente, struct mensaje buffer){
	int error, idSensorUS, idSensorIR, i, angulo, errorRespuesta;
	short int medidaUS, medidaIR, medidaUST, *medidasUS, *medidasIR, *medidasUST;
	double v,w,d, theta ;
	struct datosCinematica estadoNuevo;
	unsigned char *sbuff;
	switch (buffer._comando) {
		case COMANDO_ASIGNAR_VELOCIDAD:
			v = deSerializeDouble(buffer._argumentos);
			w = deSerializeDouble(&buffer._argumentos[4]);
			error = asignarVelocidad(v,w);
			sbuff[0] = error;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_MOVER_LINEA_RECTA:
			d = deSerializeDouble(buffer._argumentos);
			error = moverLineaRecta(d);
			sbuff[0] = error;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_GIRO_RELATIVO:
			theta = deSerializeDouble(buffer._argumentos);
			error = giroRelativo(theta);
			sbuff[0] = error;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_GOTO_XY:
			estadoNuevo.x = deSerializeDouble(buffer._argumentos);
			estadoNuevo.y = deSerializeDouble(&buffer._argumentos[8]);
			estadoNuevo.theta = deSerializeDouble(&buffer._argumentos[16]);
			error = gotoXY(estadoNuevo);
			sbuff[0] = error;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_DIAGNOSTICO_OPERATIVIDAD_MOVILIDAD:
			error = diagnosticoOperatividadMovilidad();
			sbuff[0] = error;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_ASIGNAR_DATOS_CINEMATICA:
			estadoNuevo.x = deSerializeDouble(buffer._argumentos);
			estadoNuevo.y = deSerializeDouble(&buffer._argumentos[8]);
			estadoNuevo.theta = deSerializeDouble(&buffer._argumentos[16]);
			asignarDatosCinematica(estadoNuevo);
			break;
		case COMANDO_OBTENER_DATOS_CINEMATICA:
			serializeDouble(sbuff,estadoActual.x);
			serializeDouble(&sbuff[8],estadoActual.y);
			serializeDouble(&sbuff[16],estadoActual.theta);
			errorRespuesta = escribirSocket(fdCliente, sbuff, 24);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_US:
			idSensorUS = (int)buffer._argumentos[0];
			medidaUS = 0;
			error = obtenerMedidaSensorUS(idSensorUS, &medidaUS);
			sbuff[0] = error;
			serializeShort(&sbuff[1], medidaUS);
			errorRespuesta = escribirSocket(fdCliente, sbuff, 3);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_IR:
			idSensorIR = (int)buffer._argumentos[0];
			medidaIR = 0;
			error = obtenerMedidaSensorIR(idSensorIR, &medidaIR);
			sbuff[0] = error;
			sbuff[1] = medidaIR;
			errorRespuesta = escribirSocket(fdCliente, sbuff, 2);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_US_TRASERO:
			angulo = (int)buffer._argumentos[0];
			medidaUST = 0;
			error = obtenerMedidaSensorTraseroUS(angulo, &medidaUST);
			sbuff[0] = error;
			serializeShort(&sbuff[1], medidaUST);
			errorRespuesta = escribirSocket(fdCliente, sbuff, 3);
			break;
		case COMANDO_OBTENER_BARRIDO_FRONTAL_US:
			error = obtenerBarridoFrontalUS(medidasUS);
			sbuff[0] = error;
			for(i = 0; i < 6; ++i){
				serializeShort(&sbuff[(2*i)+1], medidasUS[i]);
			}
			errorRespuesta = escribirSocket(fdCliente, sbuff, 13);
			break;
		case COMANDO_OBTENER_BARRIDO_FRONTAL_IR:
			error = obtenerBarridoFrontalIR(medidasIR);
			sbuff[0] = error;
			for(i = 0; i < 6; ++i){
				sbuff[i+1] = medidasIR[i];
			}
			errorRespuesta = escribirSocket(fdCliente, sbuff, 13);
			break;
		case COMANDO_OBTENER_BARRIDO_TRASERO_US:
			error = obtenerBarridoTraseroUS(medidasUST);
			sbuff[0] = error;
			for(i = 0; i < 5; ++i){
				serializeShort(&sbuff[(2*i)+1], medidasUST[i]);
			}
			errorRespuesta = escribirSocket(fdCliente, sbuff, 11);
			break;
		default:
			#ifdef COMANDO_DEBUG
				perror("comandos: El comando no es valido");
			#endif
			return (-1);
			break;
	}
	if(error != 0){
		#ifdef COMANDO_DEBUG
			perror("comandos: Error al ejecutar comando. \n");
		#endif
		return (-2);
	}
	if(errorRespuesta != 0){
		#ifdef COMANDO_DEBUG
			perror("comandos: Error al enviar respuesta al cliente. \n");
		#endif
		return (-3);
	}
	return 0;
}

/*******************************************************/

short int deSerializeShort(unsigned char *buf){
    if(buf == NULL){
		#ifdef COMANDO_DEBUG
			perror("deSerializeShort: Parametros incorrecto.\n");
		#endif
    	return (-1);
    }
    union{
        unsigned char c[2];
        short int val;
    }short_int;
    short_int.c[1] = *buf;
    short_int.c[0] = *(buf + 1);
    return short_int.val;
}

/*******************************************************/

void serializeShort(unsigned char *buf, short int value){
    if (buf == NULL){
		#ifdef COMANDO_DEBUG
			perror("serializeShort: Parametros incorrecto.\n");
		#endif
        return;
    }
    union{
        unsigned char c[2];
        short int val;
    }short_int;
    short_int.val = value;
    *buf = short_int.c[1];
}

/*******************************************************/

double deSerializeDouble(unsigned char *buf){
    if(buf == NULL){
		#ifdef COMANDO_DEBUG
			perror("deSerializeDouble: Parametros incorrecto.\n");
		#endif
    	return (-1);
    }
	int k;
    union{
        unsigned char c[8];
        double d;
    }doubling;
    for (k = 0; k < 8; k++){
        doubling.c[7 - k] = *(buf + k);
    }
    return doubling.d;
}

/*******************************************************/

void serializeDouble(unsigned char *buf, double value){
    int k;
	if (buf == NULL){
		#ifdef COMANDO_DEBUG
			perror("serializeDouble: Parametros incorrecto.\n");
		#endif
		return;
    }
    union {
    	unsigned char c[8];
        double d;
    } doubling;
    doubling.d = value;
    for (k = 0; k < 8; k++){
        *(buf + k) = doubling.c[7 - k];
    }
}
