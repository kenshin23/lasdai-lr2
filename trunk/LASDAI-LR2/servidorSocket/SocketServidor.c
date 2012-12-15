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
#include "definicion.h"


int inicializarConexionSocket(int *fd){
	struct sockaddr_in direccion;
	struct servent *puerto;
	int _fd;
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
	if(bind(_fd, (struct sockaddr *)&direccion, sizeof(direccion)) == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro dar el aviso al SO de la apertura del socket. \n");
		#endif
		close (_fd);
		return -1;
	}
	if (listen(_fd, 1) == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se logro dar el aviso al SO para que acepte clientes.\n");
		#endif
		close (_fd);
		return -1;
	}
	*fd = _fd;
	return 0;
}


int atenderCliente(int fd, int *fdCliente){
	socklen_t longitudCliente;
	struct sockaddr cliente;
	int _fd;
	longitudCliente = sizeof(cliente);
	_fd = accept(fd, &cliente, &longitudCliente);
	if (_fd == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: No se pudo atender al cliente.\n");
		#endif
		return -1;
	}else{
		*fdCliente = _fd;
		return 0;
	}

}

int leerSocket(int fdCliente, char *sbuf, int nBytes){
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
			leidos = leidos + aux;
		}else{
			if(aux == 0){
				return (0);
			}else{
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
}

int escribirSocket(int fdCliente, char *sbuf, int nBytes){
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
}

int terminarConexionCliente(int fdCliente){
	int error;
	error = close(fdCliente);
	if(error == 0){
		return (0);
	}else{
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intenera terminar la comunición con el cliente.\n");
		#endif
		return (-1);
	}
}


int terminarConexionSocket(int fd){
	int error;
	error = close(fd);
	if(error == 0){
		return (0);
	}else{
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intenera cerrar el socket.\n");
		#endif
		return (-1);
	}
}
