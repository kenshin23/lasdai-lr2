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

/****** Métodos ******/

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
			perror("inicializarConexionSocket: No se pudo leer la dirección del servidor.\n");
		#endif
		return (-2);
	}
	direccion.sin_family = AF_INET;
	direccion.sin_addr.s_addr = ((struct in_addr *)(host->h_addr))->s_addr;
	direccion.sin_port = puerto->s_port;
	_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_fd == -1){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: No se logro aperturar el socket.\n");
		#endif
		return (-3);
	}
	if (connect (_fd, (struct sockaddr *)&direccion, sizeof (direccion)) == -1){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("inicializarConexionSocket: No se logro realizar la conexión con el servidor.\n");
		#endif
		return -4;
	}
	return 0;
}

/**************************************************************************************************/

int leerSocket(int fd, char *sbuf, int nBytes){
	int leidos = 0, aux = 0;
	if ((fd == -1) || (sbuf == NULL) || (nBytes < 1)){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("leerSocket: Error parametros incorrecto.\n");
		#endif
		return (-1);
	}
	while(leidos < nBytes){
		aux = read(fd, sbuf+leidos, nBytes-leidos);
		if (aux > 0){
			leidos = leidos + aux;
		}else{
			if(aux == -1){
					#ifdef SOCKET_CLIENTE_DEBUG
						perror("leerSocket: Error al leer los datos.\n");
					#endif
				return (-2);
			}else{
				return (0);
			}
		}
	}
}

/**************************************************************************************************/

int escribirSocket(int fd, char *sbuf, int nBytes){
	int escritos = 0, aux = 0;
	if ((fd == -1) || (sbuf == NULL) || (nBytes < 1)){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("leerSocket: Error parametros incorrecto.\n");
		#endif
		return (-1);
	}
	while (escritos < nBytes){
		aux = write (fd, sbuf + escritos, nBytes - escritos);
		if (aux > 0){
			escritos = escritos + aux;
		}else{
			if (aux == 0)
				return escritos;
			else
				return -1;
		}
	}
	return escritos;
}

/**************************************************************************************************/

int terminarConexionSocket(int fd){
	int error;
	error = close(fd);
	if(error == 0){
		#ifdef SOCKET_CLIENTE_DEBUG
			perror("terminarConexionSocket: Error al intenera cerrar el socket.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}
