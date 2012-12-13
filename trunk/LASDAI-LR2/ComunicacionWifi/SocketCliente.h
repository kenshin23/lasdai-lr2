#ifndef _SOCKET_CLIENTE_H
#define _SOCKET_CLIENTE_H

int inicializarConexionSocket(char *hostServidor, char *servicio);

int leerSocket(int fd, char *sbuf, int nBytes);

int escribirSocket(int fd, char *sbuf, int nBytes);

int terminarConexionSocket(int fd);

#endif
