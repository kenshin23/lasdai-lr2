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
	_fd = socket (AF_INET, SOCK_STREAM, 0);
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
	direccion.sin_port = puerto->s_port;
	direccion.sin_addr.s_addr =INADDR_ANY;
	if(bind(_fd, (struct sockaddr *)&direccion, sizeof (direccion)) == -1){
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
		*_fd = fdCliente;
		return 0;
	}

}

int leerSocket(int fdCliente, char *sbuf, int nBytes){
	int Leido = 0;
	int Aux = 0;
	if ((fdCliente == -1) || (sbuf == NULL) || (nBytes < 1))
		return -1;
	while (Leido < nBytes){
		Aux = read (fdCliente, sbuf + Leido, nBytes - Leido);
		if (Aux > 0){
			Leido = Leido + Aux;
		}else{
			if (Aux == 0)
				return Leido;
			if (Aux == -1){
				return -1;
			}
		}
	}
	return Leido;
}

int escribirSocket(int fdCliente, char *sbuf, int nBytes){
	int Escrito = 0;
	int Aux = 0;
	if ((fdCliente == -1) || (sbuf == NULL) || (nBytes < 1))
		return -1;
	while (Escrito < nBytes){
		Aux = write (fdCliente, sbuf + Escrito, nBytes - Escrito);
		if (Aux > 0){
			Escrito = Escrito + Aux;
		}else{
			if (Aux == 0)
				return Escrito;
			else
				return -1;
		}
	}
	return Escrito;
}

int terminarConexionCliente(int fdCliente){
	int error;
	error = close(fdCliente);
	if(error == 0){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intenera terminar la comunición con el cliente.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}


int terminarConexionSocket(int fd){
	int error;
	error = close(fd);
	if(error == 0){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("terminarConexionSocket: Error al intenera cerrar el socket.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}
