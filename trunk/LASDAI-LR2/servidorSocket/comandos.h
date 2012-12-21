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

/** @struct mensaje
 *  @brief Estructura que almacena el contenido del mensaje enviado por el cliente al servidor.
 *  @var mensaje::_comando
 *  Member '_comando' Almacena el bytes que indica el comando a ejecutar.
 *  @var mensaje::_len
 *  Member '_len' Almacena el numero de bytes que tiene el mensaje en general (se incluye el mismo y a el comando).
 *  @var mensaje::_argumentos
 *  Member '_argumentos' Almacena el conjunto de argumentos que se envián en el mensaje, "Parámetros necesarios para ejecutar los comandos".
 */
struct mensaje{
	unsigned char _comando;
	int _len;
	unsigned char *_argumentos;
};

/**
 @brief Inicializa todos los subsistemas de la plataforma.
 @return 0 Operación exitosa en caso contrario.
		-1 Error. No se lograron inicializar todos los subsistemas de la plataforma.
*/
int inicializarRobot();

/**
 @brief Recibe el mensaje y el descriptor del cliente socket, interpreta el mensaje, ejecuta el comando y enviá la respuesta al cliente.
 @param fdCliente Descriptor del cliente.
 @param mensajeCliente Estructura del tipo "mensaje" que almacena el mensaje enviado por el cliente socket.
 @return 0 Operación exitosa en caso contrario.
		-1 El comando no es valido.
		-2 Error al ejecutar comando.
		-3 Error al enviar respuesta al cliente.
*/
int comandos(int fdCliente, struct mensaje mensajeCliente);

/**
 @brief Desactiva todos los subsistemas de la plataforma, cierra las comunicaciones.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al desactivar el robot. "Se produjo un error al intentar finalizar los subsistemas"
*/
int destruirRobot();

/**
 @brief Recibe dos bytes y retorna el "short int" (entero de 2 bytes) que resulta de la union de esos dos bytes.
 @param buf Puntero a la dirección de memoria al primer elemento del vector donde se almacenan los dos bytes.
 @return "short int" Resultado de la union.
		-1 Parámetros incorrecto.
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
