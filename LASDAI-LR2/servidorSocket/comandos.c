/**
 @file comandos.c
 @brief Implementación de las funciones que manejan la interpretación y las
 @date Diciembre, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/

#include <stdio.h>
#include "comandos.h"
#include "SocketServidor.h"
#include "../Movilidad/movilidad.h"
#include "../Percepcion/percepcion.h"
#include "definicionComandos.h"

/****** Métodos para el manejo de la comunicación por socket ******/

int inicializarRobot(){
	int error;
	error = inicializarMovilidad();
	error = iniciarComunicacionSP();
	if(error == 0){
		return (0);
	}else{
		#ifdef COMANDO_DEBUG
			perror("incializarRobot: Error al inicializar el Robot.");
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
			perror("destruirRobot: Error al destruir el Robot.");
		#endif
		return (-1);
	}
}

/*******************************************************/

int comandos(int fdCliente, struct bufferSocket buffer){
	int error, idSensorUS, idSensorIR, i, angulo;
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
			error = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_MOVER_LINEA_RECTA:
			d = deSerializeDouble(buffer._argumentos);
			error = moverLineaRecta(d);
			sbuff[0] = error;
			error = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_GIRO_RELATIVO:
			theta = deSerializeDouble(buffer._argumentos);
			error = giroRelativo(theta);
			sbuff[0] = error;
			error = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_GOTO_XY:
			estadoNuevo.x = deSerializeDouble(buffer._argumentos);
			estadoNuevo.y = deSerializeDouble(&buffer._argumentos[8]);
			estadoNuevo.theta = deSerializeDouble(&buffer._argumentos[16]);
			error = gotoXY(estadoNuevo);
			sbuff[0] = error;
			error = escribirSocket(fdCliente, sbuff, 1);
			break;
		case COMANDO_DIAGNOSTICO_OPERATIVIDAD:
			error = diagnosticoOperatividad();
			sbuff[0] = error;
			error = escribirSocket(fdCliente, sbuff, 1);
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
			error = escribirSocket(fdCliente, sbuff, 24);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_US:
			idSensorUS = (int)buffer._argumentos[0];
			medidaUS = 0;
			error = obtenerMedidaSensorUS(idSensorUS, &medidaUS);
			sbuff[0] = error;
			serializeShort(&sbuff[1], medidaUS);
			error = escribirSocket(fdCliente, sbuff, 3);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_IR:
			idSensorIR = (int)buffer._argumentos[0];
			medidaIR = 0;
			error = obtenerMedidaSensorIR(idSensorIR, &medidaIR);
			sbuff[0] = error;
			sbuff[1] = medidaIR;
			error = escribirSocket(fdCliente, sbuff, 2);
			break;
		case COMANDO_OBTENER_MEDIDA_SENSOR_US_TRASERO:
			angulo = (int)buffer._argumentos[0];
			medidaUST = 0;
			error = obtenerMedidaSensorTraseroUS(angulo, &medidaUST);
			sbuff[0] = error;
			serializeShort(&sbuff[1], medidaUST);
			error = escribirSocket(fdCliente, sbuff, 3);
			break;
		case COMANDO_OBTENER_BARRIDO_FRONTAL_US:
			error = obtenerBarridoFrontalUS(medidasUS);
			sbuff[0] = error;
			for(i = 0; i < 6; ++i){
				serializeShort(&sbuff[(2*i)+1], medidasUS[i]);
			}
			error = escribirSocket(fdCliente, sbuff, 13);
			break;
		case COMANDO_OBTENER_BARRIDO_FRONTAL_IR:
			error = obtenerBarridoFrontalIR(medidasIR);
			sbuff[0] = error;
			for(i = 0; i < 6; ++i){
				sbuff[i+1] = medidasIR[i];
			}
			error = escribirSocket(fdCliente, sbuff, 13);
			break;
		case COMANDO_OBTENER_BARRIDO_TRASERO_US:
			error = obtenerBarridoTraseroUS(medidasUST);
			sbuff[0] = error;
			for(i = 0; i < 5; ++i){
				serializeShort(&sbuff[(2*i)+1], medidasUST[i]);
			}
			error = escribirSocket(fdCliente, sbuff, 11);
			break;
		default:
			#ifdef COMANDO_DEBUG
				perror("comandos: El comando no es valido");
			#endif
			break;
	}
	if(error != 0){
		#ifdef COMANDO_DEBUG
			perror("comandos: No se pudo escribir al cliente. \n");
		#endif
		return (-1);
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
