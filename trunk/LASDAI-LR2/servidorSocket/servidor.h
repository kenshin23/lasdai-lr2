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
