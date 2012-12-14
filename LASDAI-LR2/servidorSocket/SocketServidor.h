#ifndef _SOCKET_SERVIDOR_H
#define _SOCKET_SERVIDOR_H

int inicializarConexionSocket(int *fd);

int atenderCliente(int fd);

int leerSocket(int fd, char *sbuf, int nBytes);

int escribirSocket(int fd, char *sbuf, int nBytes);

int terminarConexionSocket(int fd);

#endif
