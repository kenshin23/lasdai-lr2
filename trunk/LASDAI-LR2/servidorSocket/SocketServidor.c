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
	struct sockaddr_in Direccion;
	struct servent *Puerto;
	int Descriptor;
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
	 	return -1;
	Puerto = getservbyname (SERVICIO, "tcp");
	if (Puerto == NULL)
		return -1;
	Direccion.sin_family = AF_INET;
	Direccion.sin_port = Puerto->s_port;
	Direccion.sin_addr.s_addr =INADDR_ANY;
	if (bind (
			Descriptor,
			(struct sockaddr *)&Direccion,
			sizeof (Direccion)) == -1)
	{
		close (Descriptor);
		return -1;
	}

	if (listen (Descriptor, 1) == -1)
	{
		close (Descriptor);
		return -1;
	}
	return Descriptor;
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
