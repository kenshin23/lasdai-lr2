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
//#include "servidorSocket/servidor.h"
#include "Percepcion/percepcion.h"
#include "Movilidad/movilidad.h"
#include "MD49/md49.h"

int main() {
	int error, distancia[6];
	double angulo;
	inicializarMovilidad();
	/*error = diagnosticoOperatividadMovilidad();
	printf("Error:  %d", error);
	angulo = M_PI;
	giroRelativo(angulo);*/
	asignarVelocidad(50,0);
	do{
		obtenerBarridoFrontalUS(distancia);
		asignarVelocidad(50,0);
	}while(distancia[0] >  50 || distancia[2] >  50 || distancia[3] >  50 || distancia[4] >  50 || distancia[5] >  50);
	asignarVelocidad(0,0);
	terminarMovilidad();
	return 0;
}

