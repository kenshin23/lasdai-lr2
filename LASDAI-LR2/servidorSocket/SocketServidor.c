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
			perror("inicializarConexionSocket: \n");
		#endif
		close (_fd);
		return -1;
	}
	if (listen(_fd, 1) == -1){
		#ifdef SOCKET_SERVIDOR_DEBUG
			perror("inicializarConexionSocket: \n");
		#endif
		close (_fd);
		return -1;
	}
	*fd = _fd;
	return 0;
}


int atenderCliente(int fd){
	socklen_t Longitud_Cliente;
	struct sockaddr Cliente;
	int Hijo;
	Longitud_Cliente = sizeof (Cliente);
	Hijo = accept (fd, &Cliente, &Longitud_Cliente);
	if (Hijo == -1)
		return -1;
	return Hijo;
}

int leerSocket(int fd, char *sbuf, int nBytes){
	int Leido = 0;
	int Aux = 0;
	if ((fd == -1) || (sbuf == NULL) || (nBytes < 1))
		return -1;
	while (Leido < nBytes){
		Aux = read (fd, sbuf + Leido, nBytes - Leido);
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

int escribirSocket(int fd, char *sbuf, int nBytes){
	int Escrito = 0;
	int Aux = 0;
	if ((fd == -1) || (sbuf == NULL) || (nBytes < 1))
		return -1;
	while (Escrito < nBytes){
		Aux = write (fd, sbuf + Escrito, nBytes - Escrito);
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
