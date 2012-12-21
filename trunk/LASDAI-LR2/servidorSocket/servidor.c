#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "servidor.h"
#include "SocketServidor.h"
#include "comandos.h"

/*******************************************************/

int servidor(){
	int fd, fdCliente, error;
	inicializarRobot();
	error = inicializarConexionSocket(&fd);
	error =	atenderCliente(fd, &fdCliente);
	while(fdCliente != -1 && error == 0){
		pthread_t hebra;
		pthread_create(&hebra, NULL, (void *) atencionCliente, (void *) fdCliente);
		terminarConexionCliente(fdCliente);
		error = atenderCliente(fd, &fdCliente);
	}
	destruirRobot();
	return 0;
}

/*******************************************************/

void *atencionCliente(void * parametro){
	int fdCliente = (int)parametro, error = 0, estadoBuffer = 0;
	struct mensaje buffer;
	unsigned char * sbuf;
	while(error == 0){
		estadoBuffer = verificarBufferSocketLeer(fdCliente);
		if(estadoBuffer == 1){
			error += leerSocket(fdCliente, sbuf, 2);
			if(error == 0){
				buffer._comando = sbuf[0];
				buffer._len = sbuf[1];
				error += leerSocket(fdCliente, sbuf, buffer._len);
				if(error == 0){
					buffer._argumentos = sbuf;
					comandos(fdCliente, buffer);
				}else{
					#ifdef SERVIDOR_DEBUG
						perror("atencionCliente: Se rompio la conexion con el cliente.");
					#endif
				}
			}else{
				#ifdef SERVIDOR_DEBUG
					perror("atencionCliente: Se rompio la conexion con el cliente.");
				#endif
			}
		}else{
			if(estadoBuffer == -1){
				error = -1;
				#ifdef SERVIDOR_DEBUG
					perror("atencionCliente: Se rompio la conexion con el cliente.");
				#endif
			}
		}
	}
	terminarConexionCliente(fdCliente);
	pthread_exit(NULL);
	return 0;
}
