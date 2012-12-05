/**
 @file   percepcion.h
 @brief	 Declaración de constantes y api de funciones para el manejo del sistema de percepción usando un Arduino Mega.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: La controladora MD49 funciona bajo dos estándares de comunicación Serial. Permite el control de dos motores, y esta
 	 	 	 	diseñada especialmente para el control de motores EMG49. La declaración de constantes y api de funciones desarrolladas
 	 	 	 	a continuación representan el control del la placa MD49 en lenguaje C con comunicación serial, para la conexión de la
 	 	 	 	placa con el computador se esta usando el modulo tarjeta CP2102 USB-Serial. Los controladores de este modulo pueden
 	 	 	 	descargarse de https://www.sparkfun.com/products/198, los controladores de la CP2102 USB-Serial vienen incluidos en en el
 	 	 	 	kernel de linux Version 3.6.6.
*/

#ifndef PERCEPCION_H_
#define PERCEPCION_H_

/** API DE FUNCIONES */

/**
 @brief Apertura y configura la comunicación  serial con la MD49.
 @param fd Puntero a la dirección de memoria de la variable entera donde se almacena el numero del puerto (ID) de comunicación.
*/
int iniciarComunicacionSP(int *fd);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerMedidaSensorUS(int fd, int idSensorUS, int *distanciaUS);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerMedidaSensorIR(int fd, int idSensorIR, int *distanciaIR);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerMedidaSensorTraseroUS(int fd, int angulo, int *distanciaUST);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerBarridoFrontalUS(int fd, int *distanciasUS);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerBarridoFrontalIR(int fd, int *distanciasIR);

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la dirección de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerBarridoTraseroUS(int fd, int *distanciasUST);

/**
 @brief Finaliza la comunicación con la MD49 y cierra el puerto serial.
 @param fd Número de puerto de comunicación.
*/
int terminarComunicacionSP(int fd);

#endif /* PERCEPCION_H_ */
