#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include "SocketCliente.h"


int inicializarConexionSocket(char *hostServidor, char *servicio){
	struct sockaddr_in Direccion;
	struct servent *Puerto;
	struct hostent *Host;
	int Descriptor;
	Puerto = getservbyname (servicio, "tcp");
	if (Puerto == NULL)
		return -1;
	Host = gethostbyname (hostServidor);
	if (Host == NULL)
		return -1;
	Direccion.sin_family = AF_INET;
	Direccion.sin_addr.s_addr = ((struct in_addr *)(Host->h_addr))->s_addr;
	Direccion.sin_port = Puerto->s_port;
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor == -1)
		return -1;
	if (connect (
			Descriptor,
			(struct sockaddr *)&Direccion,
			sizeof (Direccion)) == -1)
	{
		return -1;
	}
	return Descriptor;
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
	return 0;
}

