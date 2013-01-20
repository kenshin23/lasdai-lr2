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

#include <stdio.h>
#include "Percepcion/percepcion.h"
#include "Movilidad/movilidad.h"
#include "MD49/md49.h"

int main() {


	/*iniciarComunicacionSP();
	inicializarMovilidad();
	int distanciaUS, distanciaIR, distanciasUS[6], distanciasIR[6], distanciasUST[5], i, error;
	obtenerMedidaSensorUS(1,&distanciaUS);
	printf("Sensor US 1 %d \n ", distanciaUS);
	obtenerMedidaSensorIR(1,&distanciaIR);
	printf("Sensor IR 1 %d \n ", distanciaIR);
	obtenerBarridoFrontalUS(distanciasUS);
	printf("Anillo frontalUS: ");
	for (i = 0; i < 6; ++i) {
		printf("%d - ", distanciasUS[i]);
	}
	printf("\n Anillo de frontal de IR: ");
	obtenerBarridoFrontalIR(distanciasIR);
	for (i = 0; i < 6; ++i) {
		printf("%d - ", distanciasIR[i]);
	}
	printf("\n Anillo de US trasero: ");
	obtenerBarridoTraseroUS(distanciasUST);
	for (i = 0; i < 5; ++i) {
		printf("%d - ", distanciasUST[i]);
	}
	error = diagnosticoOperatividadMovilidad();
	printf("\n error: %d \n", error);
	moverLineaRecta(50);
	terminarMovilidad();
	terminarComunicacionSP();*/
	int error;
	struct datosCinematica estado;
	estado.x = 50;
	estado.y = 50;
	estado.theta = 0;
	inicializarMovilidad();
	//asignarVelocidad(20,0);
	double angulo = M_PI/4;
	gotoXY(estado);
	estado.x = 0;
	estado.y = 0;
	estado.theta = 0;
	gotoXY(estado);
	//moverLineaRecta(10);
	//giroRelativo(angulo);
	//usleep(500000);
	//giroRelativo(-angulo);
	terminarMovilidad();

	return 0;
}

