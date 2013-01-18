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
//#include "Movilidad/movilidad.h"
//#include "ComunicacionSerial/serial.h"

int main() {

	iniciarComunicacionSP();

	int lectura[6];
	obtenerBarridoFrontalUS(lectura);
	//obtenerBarridoFrontalIR(lectura);
	int var;
	printf("\nval: ");
	for ( var = 0; var < 6; var++) {
		printf(" %d", lectura[var]);
	}
	printf("\n");
	terminarComunicacionSP();
	return 0;
}

