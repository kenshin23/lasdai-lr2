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
	char wbuf[] = "hola", sbuf[4];
	int fd, fdCliente, i = 0;
	inicializarConexionSocket(&fd);
	atenderCliente(fd,&fdCliente);
	leerSocket(fdCliente, sbuf, 4);
	printf("El cliente dijo: ");
	while(i < 4){
		printf("%c", sbuf[i]);
		i++;
	}
	printf("\n");
	escribirSocket(fdCliente, wbuf, 4);
	terminarConexionCliente(fdCliente);
	terminarConexionSocket(fd);
	return 0;
}

