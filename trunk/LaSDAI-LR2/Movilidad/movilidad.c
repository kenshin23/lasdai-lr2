/**
 @file movilidad.c
 @brief Desarrollo e implementación de la rutinas de movilidad de la plataforma LASDAI LR2.

 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com

*/

#include "movilidad.h"
#include "../MD49/md49.h"
#include "definicion.h"
#include <math.h>
#include <stdio.h>


/****** Métodos de movilidad ******/

int inicializarMovilidad(){
	int error = 0;
	if(iniciarComunicacionMD49() == 0 ){
		error += reinicializarCodificadores();
		error += activarRetroalimentacionCodificadores();
		error += activarTiempoSeguridad();
		error += asignarModoAceleracion(DEFAUL_ACELERACION_MODE);
		error += asignarModoVelocidad(DEFAUL_VELOCIDAD_MODO);
		if(error == 0 ){
			estadoActual.teta = 0;
			estadoActual.x = 0;
			estadoActual.y = 0;
			return (0);
		}else{
			#ifdef MOVILIDAD_DEBUG
				perror("inicializarMovilidad: Error al inicializar los parametros en la controladora de motores.\n");
			#endif
			return (-1);
		}
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("inicializarMovilidad: No se pudo inicializar la comunicación con la controladora de motores.\n");
		#endif
		return (-1);
	}
}

/**************************************************************************************************/

int asignarVelocidad(double v, double w){
	double v1, v2;
	int aux = 0;
	long int vm1, vm2;
	v1 = v + w*LONGITUD_EJE*0.5;
	v2 = v - w*LONGITUD_EJE*0.5;
	// 60 para pasar a minutos 127 es el indicador maximo de 122 rpm.
	v1 = v1*60*128 / M_PI*DIAMETRO_RUEDA*122 ;
	v2 = v2*60*128 / M_PI*DIAMETRO_RUEDA*122;
	vm1 = (long int)v1;
	vm2 = (long int)v2;
	aux += asignarVelocidad1(vm1);
	aux += asignarVelocidad2(vm2);
	if(aux != 0){
		#ifdef MOVILIDAD_DEBUG
			perror("asignarVelocidad: No se pudo asignar la velocidad.\n");
		#endif
		return (-1);
	}
	return (0);
}

/**************************************************************************************************/

int moverLineaRecta(double d){
	int pulsos, codificador1, codificador2, error = 0, signo = 1, rampa, distancia, vl = 0;
	pulsos = calculoNumeroPulsos(d);
	error += asignarModoVelocidad(VELOCIDAD_MODO_GIRO);
	error += reinicializarCodificadores();
	if(d < 0) signo=-1;
	distancia = fabs(d);
	if(distancia >= 60){ rampa = 1; }else{ if(distancia >= 45 && distancia < 60){ rampa = 2; }else{ if(distancia >= 25 && distancia < 45){ rampa = 3; }else{ if(distancia >= 15 && distancia < 25){ rampa = 4; }else{ rampa = 5; } } } }
	error += asignarVelocidad1(VELOCIDAD_INICIAL_RAMPA*signo);
	do{
		error += obtenerCodificadoresMotores(&codificador1, &codificador2);
		if(d < 0 && codificador1 != 0) codificador1 = (0xffffffff) - codificador1;
		if(d < 0 && codificador2 != 0) codificador2 = (0xffffffff) - codificador2;
		vl = calculoVelecidad(rampa, codificador1, codificador2, pulsos);
		error += asignarVelocidad1(vl*signo);
	}while(codificador1 < pulsos && codificador2 < pulsos);
	error += asignarVelocidad1(DETENER);
	if(error == 0){
		return (0);
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("moverLineaRecta: No se realizao el movimento de forma correcta.\n");
		#endif
		return (-1);
	}
}

/**************************************************************************************************/

int giroRelativo(double teta){


	return 0;
}

/**************************************************************************************************/

int gotoXY(struct datosCinematica estadoNuevo){


	return 0;
}

/**************************************************************************************************/

int diagnosticoOperatividad(){
	int error;
	if(obtenerError(&error) == 0){
		if(error == 0){
			return (0);
		}else{
			#ifdef MOVILIDAD_DEBUG
				perror("diagnosticoOperatividad: La controladora de motores no esta operativa, esta emitiendo un error.\n");
			#endif
			return (-2);
		}
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("diagnosticoOperatividad: No se pudo realizar el diagnostico.\n");
		#endif
		return (-1);
	}
}

/**************************************************************************************************/

void asignarDatosCinematica(struct datosCinematica estadoNuevo){
	estadoActual.x = estadoNuevo.x;
	estadoActual.y = estadoNuevo.y;
	estadoActual.teta = estadoNuevo.teta;
}

/**************************************************************************************************/

void obtenerDatosCinematica(struct datosCinematica *estado){
	estado->x = estadoActual.x;
	estado->y = estadoActual.y;
	estado->teta = estadoActual.teta;
}

/**************************************************************************************************/

int calculoNumeroPulsos(double d){
	double cm;
	cm = M_PI*DIAMETRO_RUEDA/PULSOS_REVOLUCION;
	return (int)(fabs(d)/cm);
}

/**************************************************************************************************/

int calculoVelecidad(int rampa, int codificador1, int codificador2, int pulsos){
	int vl = 16, codificador, pulsosAux;
	if(codificador1 > codificador2){ codificador = codificador1; }else{ codificador = codificador2; }
	switch (rampa) {
		case 1:
			break;
		case 2:
			pulsosAux = pulsos - 124;
			if((codificador >= 124) && (codificador < 248)){
				vl = vl*2;
			}else{
				if((codificador >= 248) && (codificador < 372)){
					vl = vl*4;
				}else{
					if((codificador >= 372) && (codificador < pulsos)){
						vl = vl*6;
					}
				}
			}
			break;
		case 3:

			break;
		case 4:
			pulsosAux = pulsos - 124;
			if((codificador >= 124) && (codificador < pulsosAux)){
				vl = vl*2;
			}
			break;
		default:
			break;
	}
	return vl;
}

/**************************************************************************************************/

int terminarMovilidad(){
	if(terminarComunicacionMD49() == 0){
		estadoActual.teta = 0;
		estadoActual.x = 0;
		estadoActual.y = 0;
		return (0);
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("terminarMovilidad: No termino de forma correcta la comunicación con la controladora de motores.\n");
		#endif
		return (-1);
	}

}
