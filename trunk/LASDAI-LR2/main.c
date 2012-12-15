/*
 * main.c
 *
 *  Created on: 29/07/2012
 *      Author: jose
 */


#include <stdio.h>
#include "Percepcion/percepcion.h"
#include "servidorSocket/SocketServidor.h"

int main(){
	/*int fd, idSensor = 0, distancia = 0;
	iniciarComunicacionSP(&fd);
	while(1){
		printf("Inserte el id del sensor IR que desea leer: ");
		scanf("%d", &idSensor );
		if(idSensor != 9){
			obtenerMedidaSensorIR(idSensor,&distancia);
			printf("distancia: %d \n", distancia);
		}else{
			break;
		}
	}
	terminarComunicacionSP(fd);*/
	unsigned char wbuf[4], sbuf[4];
	int fd, fdCliente, i = 0, aux;
	inicializarConexionSocket(&fd);
	atenderCliente(fd,&fdCliente);
	leerSocket(fdCliente, sbuf, 4);
	printf("El cliete me envio: ");
	while(i < 4){
		aux = sbuf[i];
		printf("%d \n", aux);
		i++;
	}
	i=0;
	while(i < 4){
		wbuf[i] = 16*i;
		i++;
	}
	escribirSocket(fdCliente, wbuf, 4);
	terminarConexionCliente(fdCliente);
	terminarConexionSocket(fd);
	return 0;
}

