#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include "SocketCliente.h"
#include "definicion.h"


int inicializarConexionSocket(int* fd){
	struct sockaddr_in direccion;
	struct servent *puerto;
	struct hostent *host;
	int _fd;
	puerto = getservbyname (SERVICIO, "tcp");
	if (puerto == NULL){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: No se pudo leer el puerto del servicio.\n");
		#endif
		return (-1);
	}
	host = gethostbyname (SERVIDOR_HOST);
	if (host == NULL){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: .\n");
		#endif
		return (-2);
	}
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
	direccion.sin_port = puerto->s_port;
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: .\n");
		#endif
		return (-3);
	}
	if (connect (_fd, (struct sockaddr *)&direccion, sizeof (direccion)) == -1){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: .\n");
		#endif
		return -4;
	}
	return 0;
}

int leerSocket(int fd, char *Datos, int Longitud){
	int Leido = 0;
	int Aux = 0;
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;
	while (Leido < Longitud){
		Aux = read (fd, Datos + Leido, Longitud - Leido);
		if (Aux > 0){
			Leido = Leido + Aux;
		}else{

			if (Aux == 0)
				return Leido;
			if (Aux == -1){
				switch (errno){
					case EINTR:
					case EAGAIN:
						usleep (100);
						break;
					default:
						return -1;
				}
			}
		}
	}
	return Leido;
}

int escribirSocket(int fd, char *Datos, int Longitud){
	int Escrito = 0;
	int Aux = 0;
	if ((fd == -1) || (Datos == NULL) || (Longitud < 1))
		return -1;
	while (Escrito < Longitud){
		Aux = write (fd, Datos + Escrito, Longitud - Escrito);
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

int terminarConexionSocket(int fd){
	close(fd);
	return 0;
}

