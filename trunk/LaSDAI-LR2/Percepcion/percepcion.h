/**
 @file   percepcion.h
 @brief	 Declaración de constantes y api de funciones para el manejo del sistema de percepción usando un Arduino Mega.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: El sistema de percepción esta implementando sobre un controlador Arduino Mega, controlado desde el computador bajo
  	  	  	  	estándares de comunicación Serial. Permite acceder al valor de cada uno de los sensores de la plataforma, y establece
  	  	  	  	el manejo de los puertos de expación. La declaración de constantes y api de funciones desarrolladas a continuación
  	  	  	  	representan el control del sistema de percepción en lenguaje C con comunicación serial.
*/

#ifndef PERCEPCION_H_
#define PERCEPCION_H_

/** API DE FUNCIONES */

/**
 @brief Apertura y configura la comunicación  serial con el Arduino.
 @param fd Puntero a la dirección de memoria de la variable entera donde se almacena el numero del puerto (ID) de comunicación.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al iniciar la comunicación con el Sistema de Percepción.
*/
int iniciarComunicacionSP(int *fd);

/**
 @brief Obtiene el valor del sensor Ultra Sonido que se indica en el parámetro idSensorUS.
 @param fd Número del puerto de comunicación.
 @param idSensorUS Identificador del sensor Ultra Sonido.
 @param distanciaUS Puntero a la dirección de memoria de la variable entera donde se almacena el valor del sensor.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir el comando.
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerMedidaSensorUS(int fd, int idSensorUS, int *distanciaUS);

/**
 @brief Obtiene el valor del sensor Infra Rojo que se indica en el parámetro idSensorIR.
 @param fd Número del puerto de comunicación.
 @param idSensorIR Identificador del sensor Ultra Sonido.
 @param distanciaIR Puntero a la dirección de memoria de la variable entera donde se almacena el valor del sensor.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir el comando.
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerMedidaSensorIR(int fd, int idSensorIR, int *distanciaIR);

/**
 @brief Obtiene el valor del sensor Ultra Sonido ubicado en la parte trasera con un angulo especifico (50 - 130).
 @param fd Número del puerto de comunicación.
 @param angulo Ángulo de posición del sensor Ultra Sonido trasero.
 @param distanciaUST Puntero a la dirección de memoria de la variable entera donde se almacena el valor del sensor.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir el comando.
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerMedidaSensorTraseroUS(int fd, int angulo, int *distanciaUST);

/**
 @brief Actualiza el vector con los valores del barrido de los 6 sensores Ultra Sonido delanteros.
 @param fd Número del puerto de comunicación.
 @param distanciasUS puntero a la dirección de memoria del vector que almacena el valor de los 6 sensores US delanteros.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intenetar escribir el comando..
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerBarridoFrontalUS(int fd, int *distanciasUS);

/**
 @brief Actualiza el vector con los valores del barrido de los 6 sensores IR delanteros.
 @param fd Número del puerto de comunicación.
 @param distanciasIR puntero a la dirección de memoria del vector que almacena el valor de los 6 sensores IR delanteros.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intenetar escribir el comando..
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerBarridoFrontalIR(int fd, int *distanciasIR);

/**
 @brief Actualiza el vector con los valores del barrido en 5 posiciones del sensor US delantero.
 @param fd Número del puerto de comunicación.
 @param distanciasUST puntero a la dirección de memoria del vector que almacena el valor del barrido US del sensor trasero.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir el comando..
		-2 Error el comando no se ejecuto correctamente.
*/
int obtenerBarridoTraseroUS(int fd, int *distanciasUST);

/**
 @brief Finaliza la comunicación con el Sistema de Percepción y cierra el puerto serial.
 @param fd Número de puerto de comunicación.
  	  	0 Operación exitosa en caso contrario.
	   -1 Error al terminar la comunicación con el Sistema de Percepción.
*/
int terminarComunicacionSP(int fd);

#endif /* PERCEPCION_H_ */
