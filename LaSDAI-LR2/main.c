/*
 * main.c
 *
 *  Created on: 29/07/2012
 *      Author: jose
 */

//PRUEBa}

#include <stdio.h>
#include "Percepcion/percepcion.h"

int main(){
	int fd, idSensor, distancia;
	iniciarComunicacionSP(&fd);
	while(1){
		scanf("Inserte el id del sensor US que desea leer: %d", idSensor );
		if(idSensor != 9){
			obtenerMedidaSensorUS(fd,idSensor,&distancia);
		}else{
			break;
		}
	}
	terminarComunicacionSP(fd);
	return 0;
}

