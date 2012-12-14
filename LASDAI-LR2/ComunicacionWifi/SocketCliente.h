
#ifndef _SOCKET_CLIENTE_H
#define _SOCKET_CLIENTE_H

int inicializarConexionSocket(int *fd);

int leerSocket(int fd, char *sbuf, int nBytes);

int escribirSocket(int fd, char *sbuf, int nBytes);

int terminarConexionSocket(int fd);

#endif
