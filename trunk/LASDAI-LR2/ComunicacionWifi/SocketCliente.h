#ifndef _SOCKET_CLIENTE_H
#define _SOCKET_CLIENTE_H

int Abre_Conexion_Inet (char *Host_Servidor, char *Servicio);
int Lee_SocketCliente (int fd, char *Datos, int Longitud);
int Escribe_SocketCliente (int fd, char *Datos, int Longitud);

#endif
