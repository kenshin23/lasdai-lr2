/**
 @file   comandos.h
 @brief  Declaración de constantes y api de funciones para el manejo de comandos del servidor socket.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: .

*/

#ifndef _COMANDOS_H
#define _COMANDOS_H

/** @struct datosCinematica
 *  @brief Estructura que contiene los datos de la cinemática de la plataforma, posición y orientación en el plano cartesiano.
 *  @var datosCinematica::X
 *  Member 'x' Almacena la coordenada del robot en el eje de las abscisas (cm).
 *  @var datosCinematica::Y
 *  Member 'y' Almacena la coordenada del robot en el eje de las ordenadas (cm).
 *  @var datosCinematica::teta
 *  Member 'teta' Almacena el ángulo que representa la orientación de la plataforma (rad).
 */
struct mensaje{
	unsigned char _comando;
	int _len;
	unsigned char *_argumentos;
};

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
int inicializarRobot();

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
int comandos(int fdCliente, struct mensaje buffer);

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
int destruirRobot();

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
short int deSerializeShort(unsigned char *buf);

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
void serializeShort(unsigned char *buf, short int value);

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
double deSerializeDouble(unsigned char *buf);

/**
 @brief Si hay un cliente en espera lo atiende si no se bloquea hasta llegue un cliente.
 @param fd Descriptor de Servidor.
 @param fdCliente Puntero a la dirección de memoria donde se almacenara el descriptor asignado al cliente.
 @return 0 Operación exitosa en caso contrario.
		-1 No se pudo atender al cliente..
*/
void serializeDouble(unsigned char *buf, double value);

#endif
