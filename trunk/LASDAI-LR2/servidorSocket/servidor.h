/**
 @file   SocketServidor .h
 @brief  Declaración de constantes y api de funciones para el manejo de la servidor socket.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: Se implementa un servidor socket TCP de la familia AF_INET lo que permite que socket pueda ser
 	 	 	 	local o remoto.

*/

#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include "comandos.h"

#define SERVIDOR_DEBUG

/** API DE FUNCIONES */

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
int servidor();

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
void *atencionCliente(void * parametro);

#endif /* _SERVIDOR_H */
