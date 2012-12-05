/*
 * main.c
 *
 *  Created on: 29/07/2012
 *      Author: jose
 */


#include <stdio.h>
#include "Percepcion/percepcion.h"

int main(){
	int fd, idSensor = 0, distancia = 0;
	iniciarComunicacionSP(&fd);
	while(1){
		printf("Inserte el id del sensor IR que desea leer: ");
		scanf("%d", &idSensor );
		if(idSensor != 9){
			obtenerMedidaSensorIR(fd,idSensor,&distancia);
			printf("distancia: %d \n", distancia);
		}else{
			break;
		}
	}
	terminarComunicacionSP(fd);
	return 0;
}

