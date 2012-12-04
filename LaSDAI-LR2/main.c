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
	int fd, idSensor = 0, distancia = 10;
	iniciarComunicacionSP(&fd);
	while(1){
		printf("Inserte el id del sensor US que desea leer: ");
		scanf("%d", &idSensor );
		if(idSensor != 9){
			obtenerMedidaSensorUS(fd,idSensor,&distancia);
			printf("distancia: %d \n", distancia);
		}else{
			break;
		}
	}
	terminarComunicacionSP(fd);
	return 0;
}

