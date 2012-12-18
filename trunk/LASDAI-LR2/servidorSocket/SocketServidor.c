/**
 @file socketServidor.c
 @brief Implementación de las funciones que manejo de la comunicación por sockets, definidas en SocketServidor.h
 @date Diciembre, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include "SocketServidor.h"
#include "definicionSocket.h"

/****** Métodos para el manejo de la comunicación por socket ******/

int inicializarConexionSocket(int *fd){
	struct sockaddr_in direccion;
	struct servent *puerto;
	int _fd;
	/** Apertura el socket del servidor **/
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(_fd == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro aperturar el socket.\n");
		#endif
		return (-1);
	}
	puerto = getservbyname(SERVICIO, "tcp");
	if (puerto == NULL){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se pudo leer el puerto del servicio.\n");
		#endif
		return (-2);
	}
	direccion.sin_family = AF_INET;
	direccion.sin_port = htons(puerto->s_port);
	direccion.sin_addr.s_addr =INADDR_ANY;
	/** Conecta al Socket al servicio y avisa al SO **/
	if(bind(_fd, (struct sockaddr *)&direccion, sizeof(direccion)) == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro asociar el socket al servicio. \n");
		#endif
		close (_fd);
		return -3;
	}
	/** Se informa al SO que puede recibir clientes y se asigna un maximo de clientes que pueden esperar en cola **/
	if (listen(_fd, 1) == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro dar el aviso al SO para que acepte clientes.\n");
		#endif
		close (_fd);
		return -4;
	}
	*fd = _fd;
	return 0;
}

/*******************************************************/

int atenderCliente(int fd, int *fdCliente){
	socklen_t longitudCliente;
	struct sockaddr cliente;
	int _fd;
	longitudCliente = sizeof(cliente);
	/** Si hay un cliente en cola lo atiende, se bloquea hasta que no llegue un cliente **/
	_fd = accept(fd, &cliente, &longitudCliente);
	if (_fd == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro atender al cliente.\n");
		#endif
		return -1;
	}else{
		*fdCliente = _fd;
		return 0;
	}

}

/*******************************************************/

int leerSocket(int fdCliente, unsigned char *sbuf, int nBytes){
	int leidos = 0, aux = 0;
	if((fdCliente == -1) || (sbuf == NULL) || (nBytes < 1)){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("leerSocket: Error parametros incorrecto.\n");
		#endif
		return (-1);
	}
	while(leidos < nBytes){
		aux = read(fdCliente, sbuf + leidos, nBytes - leidos);
		if (aux > 0){
			leidos += aux;
		}else{
			if(aux != 0){
				switch (errno){
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						#ifdef SOCKET_CLIENTE_DEBUG
							perror("leerSocket: Error al leer los datos.\n");
						#endif
						return (-2);
				}
			}
		}
	}
	return (0);
}

/*******************************************************/

int escribirSocket(int fdCliente, unsigned char *sbuf, int nBytes){
	int escritos = 0, aux = 0;
	if ((fdCliente == -1) || (sbuf == NULL) || (nBytes < 1)){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("escribirSocket: Error parametros incorrecto.\n");
		#endif
		return (-1);
	}
	while(escritos < nBytes){
		aux = write(fdCliente, sbuf + escritos, nBytes - escritos);
		if(aux > 0){
			escritos = escritos + aux;
		}else{
			#ifdef SOCKET_CLIENTE_DEBUG
				perror("escribirSocket: Error no se logro escribir el bufer corretamente.\n");
			#endif
			return (-2);
		}
	}
	return (0);
}

/*******************************************************/

int verificarBufferSocketLeer(int fdCliente){
	int aux;
	fd_set _fd;
	struct timeval tiempoSalida;
	tiempoSalida.tv_sec  = 0;
	tiempoSalida.tv_usec = TIMEOUT_USEC;
	FD_ZERO(&_fd);
	FD_SET(fdCliente,&_fd);
	aux = select(FD_SETSIZE,&_fd,NULL,NULL,&tiempoSalida);
	if(aux > 0 ){
		return (1);
	}else{
		if(aux == 0){
			 return (0);
		}else{
			#ifdef SERIAL_DEBUG
				perror("verificarBufferSocket: Error no se logro censar si hay datos en el bufer socket con el cliente.\n");
			#endif
		  return (-1);
		}
	}
}

/*******************************************************/

int verificarBufferSocketEscribir(int fdCliente){
	int aux;
	fd_set _fd;
	struct timeval tiempoSalida;
	tiempoSalida.tv_sec  = 0;
	tiempoSalida.tv_usec = TIMEOUT_USEC;
	FD_ZERO(&_fd);
	FD_SET(fdCliente,&_fd);
	aux = select(FD_SETSIZE,NULL,&_fd,NULL,&tiempoSalida);
	if(aux > 0 ){
		return (1);
	}else{
		if(aux == 0){
			 return (0);
		}else{
			#ifdef SERIAL_DEBUG
				perror("verificarBufferSocket: Error no se logro censar si hay datos en el bufer socket con el cliente.\n");
			#endif
		  return (-1);
		}
	}
}

/*******************************************************/

int terminarConexionCliente(int fdCliente){
	int error;
	error = close(fdCliente);
	if(error == 0){
		return (0);
	}else{
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intentar terminar la comunición con el cliente.\n");
		#endif
		return (-1);
	}
}

/*******************************************************/

int terminarConexionSocket(int fd){
	int error;
	error = close(fd);
	if(error == 0){
		return (0);
	}else{
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intentar cerrar el socket.\n");
		#endif
		return (-1);
	}
}
