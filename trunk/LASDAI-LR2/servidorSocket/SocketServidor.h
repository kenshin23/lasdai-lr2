/********************************************************************************
* This program is free software; you can redistribute it and/or modify it under *
* the terms of the GNU General Public License as published by the Free Software *
* Foundation; either version 2 of the License, or (at your option) any later 	*
* version. This program is distributed in the hope that it will be useful, but 	*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more *
* details. You should have received a copy of the GNU General Public License 	*
* along with this program; if not, write to the Free Software Foundation, Inc., *
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.						*
* (c) Copyright 2012 José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.	*				*
********************************************************************************/

/**
 @file   SocketServidor.h
 @brief  Declaración de constantes y api de funciones para el manejo de la servidor socket.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: Se implementa un servidor socket TCP de la familia AF_INET lo que permite que socket pueda ser
 	 	 	 	local o remoto.

*/

#ifndef _SOCKET_SERVIDOR_H
#define _SOCKET_SERVIDOR_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include "definicionSocket.h"

/**
 @brief Apertura el socket del servidor, asocia el socket al servicio "servicioLr2", informa al SO
 	 	que se esta listo para atender el servicio y asigna el numero máximo de cliente que pueden esperar en colas.
 @param fd Puntero a la dirección de memoria donde ce almacena el descriptor asigando al socket del servidor.
 @return 0 Operación exitosa en caso contrario.
		-1 Error No se logro aperturar el socket..
		-2 Error No se pudo leer el puerto del servicio.
		-3 Error No se logro asociar el socket al servicio.
		-4 Error No se logro dar el aviso al SO para que acepte clientes.
*/
int inicializarConexionSocket(int *fd);

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
int atenderCliente(int fd, int *fdCliente);

/**
 @brief Lee del buffer un numero de bytes indicados (Se bloquea hasta no leer nBytes).
 @param fdCliente Descriptor del cliente que esta atendiendo el socket.
 @param sbuf Puntero al vector donde se almacenaran los datos que se lean del buffer.
 @param nBytes Numero de Bytes a leer del buffer.
 @return 0 Operación exitosa en caso contrario.
		-1 Error parámetros incorrecto..
		-2 Error No se lograron leer los datos.
*/
int leerSocket(int fdCliente, unsigned char *sbuf, int nBytes);

/**
 @brief Enviá al buffer del cliente un número de bytes indicados.
 @param fdCliente Descriptor del cliente que esta atendiendo el socket.
 @param sbuf Puntero al vector donde se almacenan los datos que se van a enviar al cliente.
 @param nBytes Numero de Bytes a enviar al cliente buffer.
 @return 0 Operación exitosa en caso contrario.
		-1 Error parámetros incorrecto..
		-2 Error no se logro escribir el buffer correctamente.
*/
int escribirSocket(int fdCliente, unsigned char *sbuf, int nBytes);

/**
 @brief Verifica si hay algo que leer en el buffer, si no hay nada se bloque hasta que llegue algo o pase TIMEOUT_USEC.
 @param fdCliente Descriptor del cliente que esta atendiendo el socket.
 @return 0 Se termino TIMEOUT_USEC y el buffer esta vacío no hay nada que leer.
		 1 Hay bytes en el buffer.
		-1 Error al verificar el buffer el cliente no esta disponible.
*/
int verificarBufferSocketLeer(int fdCliente);

/**
 @brief Verifica si se puede escribir al buffer sin bloqueo, si no se puede escribir se bloque hasta que se pueda o pase TIMEOUT_USEC.
 @param fdCliente Descriptor del cliente que esta atendiendo el socket.
 @return 0 Se termino TIMEOUT_USEC y el buffer no esta listo para escritura.
		 1 El buffer esta listo para escritura.
		-1 Error al verificar el buffer el cliente no esta disponible.
*/
int verificarBufferSocketEscribir(int fdCliente);

/**
 @brief Cierra el socket con el cliente.
 @param fdCliente Descriptor del cliente que esta atendiendo el socket.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar terminar la comunición con el cliente.
*/
int terminarConexionCliente(int fdCliente);

/**
 @brief Cierra el socket del servidor.
 @param fd Descriptor del socket Servidor.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar cerrar el socket..
*/
int terminarConexionSocket(int fd);

#endif  /* _SOCKET_SERVIDOR_H */
