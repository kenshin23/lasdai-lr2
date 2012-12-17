#include <stdio.h>
#include "comandos.h"
#include "../Movilidad/movilidad.h"
#include "../Percepcion/percepcion.h"
#include "definicionComandos.h"

/*******************************************************/

void * comandos(void * parametrosHilo){
	struct parametrohilo parametros = (struct parametrohilo)parametrosHilo;
	int fdCliente = parametros.fdCliente;
	int error;
	char *sbuf;
	struct bufferSocket buffer = parametros.buf;
	switch (buffer._comando) {
		case ASIGNAR_VELOCIDAD:
			double v, w;
			v = deSerializeDouble(buffer._argumentos);
			w = deSerializeDouble(&buffer._argumentos[4]);
			error = asignarVelocidad(v,w);
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case MOVER_LINEA_RECTA:
			double d;
			d = deSerializeDouble(buffer._argumentos);
			error = moverLineaRecta(d);
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case GIRO_RELATIVO:
			double theta;
			theta = deSerializeDouble(buffer._argumentos);
			error = giroRelativo(theta);
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case GOTO_XY:
			struct datosCinematica estadoNuevo;
			estadoNuevo.x = deSerializeDouble(buffer._argumentos);
			estadoNuevo.y = deSerializeDouble(&buffer._argumentos[8]);
			estadoNuevo.theta = deSerializeDouble(&buffer._argumentos[16]);
			error = gotoXY(estadoNuevo);
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case DIAGNOSTICO_OPERATIVIDAD:
			error = diagnosticoOperatividad();
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case ASIGNAR_DATOS_CINEMATICA:
			struct datosCinematica estadoNuevo;
			estadoNuevo.x = deSerializeDouble(buffer._argumentos);
			estadoNuevo.y = deSerializeDouble(&buffer._argumentos[8]);
			estadoNuevo.theta = deSerializeDouble(&buffer._argumentos[16]);
			error = asignarDatosCinematica(estadoNuevo);
			sbuf[0] = error;
			error = escribirSocket(fdCliente, sbuf, 1);
			break;
		case OBTENER_DATOS_CINEMATICA:
			serializeDouble(&sbuf,estadoActual.x);
			serializeDouble(&sbuf[8],estadoActual.y);
			serializeDouble(&sbuf[16],estadoActual.theta);
			error = escribirSocket(fdCliente, sbuf, 24);
			break;
		case OBTENER_MEDIDA_SENSOR_US:
			int idSensorUS = (int)buffer._argumentos[0];
			short int medidaUS = 0;
			error = obtenerMedidaSensorUS(idSensorUS, &medidaUS);
			sbuf[0] = error;
			serializeShort(&sbuf[1], medidaUS);
			error = escribirSocket(fdCliente, sbuf, 3);
			break;
		case OBTENER_MEDIDA_SENSOR_IR:
			int idSensorIR = (int)buffer._argumentos[0];
			uint8_t medidaIR = 0;
			error = obtenerMedidaSensorIR(idSensorIR, &medidaIR);
			sbuf[0] = error;
			sbuf[1] = medidaIR;
			error = escribirSocket(fdCliente, sbuf, 2);
			break;
		case OBTENER_MEDIDA_SENSOR_US_TRASERO:
			int angulo = (int)buffer._argumentos[0];
			short int medidaUST = 0;
			error = obtenerMedidaSensorTraseroUS(angulo, &medidaUST);
			sbuf[0] = error;
			serializeShort(&sbuf[1], medidaUS);
			error = escribirSocket(fdCliente, sbuf, 3);
			break;
		case OBTENER_BARRIDO_FRONTAL_US:
			short int *medidasUS;

			break;
		case OBTENER_BARRIDO_FRONTAL_IR:
			break;
		case OBTENER_BARRIDO_TRASERO_US:
			break;
		default:
			break;
	}
	if(error != 0){
		#ifdef COMANDO_DEBUG
			perror("comandos: No se pudo escribir al cliente. \n");
		#endif
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
