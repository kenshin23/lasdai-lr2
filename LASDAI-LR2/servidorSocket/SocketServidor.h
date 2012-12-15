#ifndef _SOCKET_SERVIDOR_H
#define _SOCKET_SERVIDOR_H

int inicializarConexionSocket(int *fd);

int atenderCliente(int fd, int *fdCliente);

int leerSocket(int fdCliente, char *sbuf, int nBytes);

int escribirSocket(int fdCliente, char *sbuf, int nBytes);

int terminarConexionCliente(int fdCliente);

int terminarConexionSocket(int fd);

#endif
