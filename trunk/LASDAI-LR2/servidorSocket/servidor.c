/**
 @file servidor.c
 @brief Desarrollo e implementación de las funciones del servidor de la plataforma LASDAI LR2 definidas en servidor.h.
 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

#include "servidor.h"

/****** Funciones de servidor de la plataforma LASDAI LR2******/

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
	if(error != 0 ){
		#ifdef SERVIDOR_DEBUG
			perror("servidor: Error en el  servidor.");
		#endif
		return (-1);
	}
	destruirRobot();
	return 0;
}

/*******************************************************/

void *atencionCliente(void * parametro){
	int fdCliente = (int)parametro, error = 0, estadoBuffer = 0;
	struct mensaje mensajeCliente;
	unsigned char * sbuf;
	while(error == 0){
		estadoBuffer = verificarBufferSocketLeer(fdCliente);
		if(estadoBuffer == 1){
			error += leerSocket(fdCliente, sbuf, 2);
			if(error == 0){
				mensajeCliente._comando = sbuf[0];
				mensajeCliente._len = sbuf[1];
				error += leerSocket(fdCliente, sbuf, mensajeCliente._len);
				if(error == 0){
					mensajeCliente._argumentos = sbuf;
					comandos(fdCliente, mensajeCliente);
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
