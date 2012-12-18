/**
 @file   md49.h
 @brief  Declaración de constantes y api de funciones para el manejo de los motores EMG49 con reductora 49:1 usando la controladora MD49.
 @date   Junio, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: La controladora MD49 funciona bajo dos estándares de comunicación Serial. Permite el control de dos motores, y esta
 	 	 	 	diseñada especialmente para el control de motores EMG49. La declaración de constantes y api de funciones desarrolladas
 	 	 	 	a continuación representan el control del la placa MD49 en lenguaje C con comunicación serial, para la conexión de la
 	 	 	 	placa con el computador se esta usando el modulo tarjeta CP2102 USB-Serial. Los controladores de este modulo pueden
 	 	 	 	descargarse de https://www.sparkfun.com/products/198, los controladores de la CP2102 USB-Serial vienen incluidos en en el
 	 	 	 	kernel de linux Version 3.6.6.
*/

#ifndef _SOCKET_SERVIDOR_H
#define _SOCKET_SERVIDOR_H

/** API DE FUNCIONES */

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int inicializarConexionSocket(int *fd);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int atenderCliente(int fd, int *fdCliente);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int leerSocket(int fdCliente, unsigned char *sbuf, int nBytes);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int escribirSocket(int fdCliente, unsigned char *sbuf, int nBytes);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int verificarBufferSocketLeer(int fdCliente);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int verificarBufferSocketEscribir(int fdCliente);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int terminarConexionCliente(int fdCliente);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int terminarConexionSocket(int fd);

#endif
