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
 @file movilidad.c
 @brief Desarrollo e implementación de la rutinas de movilidad de la plataforma LASDAI LR2.
 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

*/

#include "movilidad.h"

/****** Métodos de movilidad ******/

int inicializarMovilidad(){
	int error = 0;
	if(iniciarComunicacionMD49() == 0 ){
		error += reinicializarCodificadores();
//		error += activarRetroalimentacionCodificadores();
//		error += activarTiempoSeguridad();
//		error += asignarModoAceleracion(DEFAUL_ACELERACION_MODE);
//		error += asignarModoVelocidad(DEFAUL_VELOCIDAD_MODO);
//		if(error == 0 ){
//			estadoActual.theta = 0;
//			estadoActual.x = 0;
//			estadoActual.y = 0;
//			return (0);
//		}else{
//			#ifdef MOVILIDAD_DEBUG
//				perror("inicializarMovilidad: Error al inicializar los parametros en la controladora de motores.\n");
//			#endif
//			return (-2);
//		}
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
	// 60 para pasar a minutos, 127 es el indicador maximo de 122 rpm.
	v1 = v1*60*128/M_PI*DIAMETRO_RUEDA*122 ;
	v2 = v2*60*128/M_PI*DIAMETRO_RUEDA*122;
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
	int pulsos, codificador1, codificador2, error = 0, signo = 1;
	int aux = 2, aux2, vl = 0, cambios, cambiosHechos = 0, pulsosDesaceleracion;
	double distancia;
	pulsos = calculoNumeroPulsos(d);
	error += asignarModoVelocidad(VELOCIDAD_MODO_GIRO);
	error += reinicializarCodificadores();
	if(d < 0) signo=-1;
	distancia = fabs(d);
	cambios = calculoCambios(distancia);
	pulsosDesaceleracion = pulsos-(cambios/2)*PULSOS_DE_CAMBIOS_RAMPA;
	error += asignarVelocidad1(VELOCIDAD_INICIAL_RAMPA*signo);
	do{
		error += obtenerCodificadoresMotores(&codificador1, &codificador2);
		if(d < 0 && codificador1 != 0) codificador1 = (0xffffffff) - codificador1;
		if(d < 0 && codificador2 != 0) codificador2 = (0xffffffff) - codificador2;
		if((cambiosHechos < cambios/2) && (codificador1 >= PULSOS_DE_CAMBIOS_RAMPA*(cambiosHechos+1))){
			vl = VELOCIDAD_INICIAL_RAMPA*aux;
			cambiosHechos++;
			aux = aux+2;
			aux2 = aux-2;
		}else{
			if(cambiosHechos >= cambios/2 ){
				if((cambiosHechos < cambios) && (codificador1 >= pulsosDesaceleracion)){
					aux2 = aux2-2;
					if(aux2 == 0) aux2 = 1;
					vl = VELOCIDAD_INICIAL_RAMPA*aux2;
					cambiosHechos++;
					pulsosDesaceleracion = pulsosDesaceleracion + PULSOS_DE_CAMBIOS_RAMPA;
				}
			}
		}
		error += asignarVelocidad1(vl*signo);
	}while(codificador1 < pulsos || codificador2 < pulsos);
	error += asignarVelocidad1(DETENER);
	error += asignarModoVelocidad(DEFAUL_VELOCIDAD_MODO);
	if(error == 0){
		return (0);
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("moverLineaRecta: No se realizo el movimiento de forma correcta.\n");
		#endif
		return (-1);
	}
}

/**************************************************************************************************/

int giroRelativo(double theta){
	int pulsos, codificador1, codificador2, error = 0, signo = 1;
	int aux = 2, aux2, w = 0, cambios, cambiosHechos = 0, pulsosDesaceleracion;
	double distancia;
	theta = calcularAnguloGiroRelativo(theta);
	distancia = (theta*LONGITUD_EJE)/2;
	pulsos = calculoNumeroPulsos(distancia);
	error += asignarModoVelocidad(VELOCIDAD_MODO_GIRO);
	error += reinicializarCodificadores();
	if(theta > 0) signo=-1;
	cambios = calculoCambios(fabs(distancia));
	pulsosDesaceleracion = pulsos-(cambios/2)*PULSOS_DE_CAMBIOS_RAMPA;
	error += asignarVelocidad2(VELOCIDAD_INICIAL_RAMPA*signo);
	do{
		error += obtenerCodificadoresMotores(&codificador1, &codificador2);
		if(theta < 0){
			if(codificador2 != 0) codificador2 = (0xffffffff) - codificador2;
		}else{
			if(codificador1 != 0) codificador1 = (0xffffffff) - codificador1;
		}
		if((cambiosHechos < cambios/2) && (codificador1 >= PULSOS_DE_CAMBIOS_RAMPA*(cambiosHechos+1))){
			w = VELOCIDAD_INICIAL_RAMPA*aux;
			cambiosHechos++;
			aux = aux+2;
			aux2 = aux-2;
		}else{
			if(cambiosHechos >= cambios/2 ){
				if((cambiosHechos < cambios) && (codificador1 >= pulsosDesaceleracion)){
					aux2 = aux2-2;
					if(aux2 == 0) aux2 = 1;
					w = VELOCIDAD_INICIAL_RAMPA*aux2;
					cambiosHechos++;
					pulsosDesaceleracion = pulsosDesaceleracion + PULSOS_DE_CAMBIOS_RAMPA;
				}
			}
		}
		error += asignarVelocidad2(w*signo);
	}while(codificador1 < pulsos || codificador2 < pulsos);
	error += asignarVelocidad2(DETENER);
	error += asignarModoVelocidad(DEFAUL_VELOCIDAD_MODO);
	if(error == 0){
		return (0);
	}else{
		#ifdef MOVILIDAD_DEBUG
			perror("giroRelativo: No se realizo el movimiento de forma correcta.\n");
		#endif
		return (-1);
	}
}

/**************************************************************************************************/

int gotoXY(struct datosCinematica estadoNuevo){
	int error = 0;
	double distancia, catetoOpuesto, catetoAdyacente ,thetaAuxiliar, thetaGiro;
	catetoOpuesto = estadoNuevo.y - estadoActual.y;
	catetoAdyacente = estadoNuevo.x - estadoActual.x;
	distancia = sqrt(pow(catetoAdyacente, 2) + pow(catetoOpuesto,2));
	thetaAuxiliar = calculoAnguloGotoXY(distancia, catetoAdyacente,  catetoOpuesto);
	thetaGiro = thetaAuxiliar - estadoActual.theta;
	error += giroRelativo(thetaGiro);
	estadoActual.theta = thetaAuxiliar;
	usleep(RETARDO);
	error += moverLineaRecta(distancia);
	thetaGiro = estadoNuevo.theta - estadoActual.theta;
	usleep(RETARDO);
	error += giroRelativo(thetaGiro);
	if(error == 0){
		asignarDatosCinematica(estadoNuevo);
		return (0);
	}else{
		#ifdef MOVILIDAD_DEBUG
		perror("gotoXY: No se logro ir a la posicion (x,y,theta)\n");
		#endif
		return (-1);
	}

}

/**************************************************************************************************/

int diagnosticoOperatividadMovilidad(){
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
	estadoActual.theta = estadoNuevo.theta;
}

/**************************************************************************************************/

struct datosCinematica obtenerDatosCinematica(){
	return estadoActual;
}

/**************************************************************************************************/

int calculoNumeroPulsos(double d){
	double cm;
	int pulsos;
	cm = M_PI*DIAMETRO_RUEDA/PULSOS_REVOLUCION;
	pulsos = (int)(fabs(d)/cm);
	return pulsos;
}

/**************************************************************************************************/

int calculoCambios(int distancia){
	int cambios;
	if(distancia >= 60){
		cambios = 8;
	}else{
		if(distancia >= 45 && distancia < 60){
			cambios = 6;
		}else{
			if(distancia >= 25 && distancia < 45){
				cambios = 4;
			}else{
				if(distancia >= 15 && distancia < 25){
					cambios = 2;
				}else{
					cambios = 0;
				}
			}
		}
	}
	return cambios;
}

/**************************************************************************************************/

double calcularAnguloGiroRelativo(double theta){
	if(theta > (2*M_PI) || theta < (-2*M_PI)){
		theta = theta - (int)(theta/(2*M_PI))*(2*M_PI);
	}
	if(theta > M_PI || theta < -M_PI){
		theta = theta-((2*M_PI)*(theta/fabs(theta)));
	}
	return theta;
}

/**************************************************************************************************/

double calculoAnguloGotoXY(double distancia, double catetoAdyacente, double catetoOpuesto){
	double theta;
	theta = asin(catetoOpuesto/distancia);
	if(catetoOpuesto >= 0){
		if(catetoAdyacente >= 0){
			return theta;		
		}else{
			theta = (M_PI - theta);
			return theta;
		}
	}else{
		if(catetoAdyacente >= 0){
			theta = (2*M_PI + theta);
			return theta;		
		}else{
			theta = (M_PI + theta);
			return theta;
		}
	}
}

/**************************************************************************************************/

int terminarMovilidad(){
	if(terminarComunicacionMD49() == 0){
		estadoActual.theta = 0;
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
