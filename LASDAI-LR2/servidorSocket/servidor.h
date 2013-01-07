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
 @file   servidor.h
 @brief  Declaración de constantes y api de funciones del servidor de control de LASDAI LR2.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: El servidor atiende clientes locales o remotos del servicio socket, asigna un hilo de ejecución para cada cliente.

*/

#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "SocketServidor.h"
#include "comandos.h"

/**
 @brief Inicializa todos los servicios de la plataforma, apertura el socket, atiende a los cliente y le asigna un hilo de
 	 	 ejecución a cada cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 Error en el servidor.
*/
int servidor();

/**
 @brief Esta función es ejecutada por cada hilo de ejecución, recibe y atiende las solicitudes del cliente.
 @param parametro contiene el descriptor del cliente.
*/
void *atencionCliente(void * parametro);

#endif /* _SERVIDOR_H */
