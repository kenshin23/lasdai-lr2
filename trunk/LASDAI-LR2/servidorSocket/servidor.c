#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "servidor.h"
#include "SocketServidor.h"

/*******************************************************/

int servidor(){
	int fd, fdCliente, error;
	error = inicializarConexionSocket(&fd);
	error =	atenderCliente(fd, &fdCliente);
	while(fdCliente != -1 && error == 0){
		pthread_t hebra;
		pthread_create(&hebra, NULL, (void *) atencionCliente, (void *) fdCliente);
		terminarConexionCliente(fdCliente);
		error = atenderCliente(fd, &fdCliente);
	}
	return 0;
}

/*******************************************************/

void *atencionCliente(void * estructura){

	return 0;
}
