/**
 @file   md49.h
 @brief  Declaración de constantes y api de funciones para el manejo de los motores EMG49 con reductora 49:1 usando la controladora MD49.
 @date   Junio, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com

 Algunos datos: La controladora MD49 funciona bajo dos estandares de comunicación Serial. Permite el control de dos motores, y esta
 	 	 	 	diseñada especialmente para el control de motores EMG49. Las declaración  de constantes y api de funciones desarrolladas
 	 	 	 	a continuacion representan el control del la placa MD49 en lenguaje C con comunicacion serial, para la conexion de la
 	 	 	 	placa con el computador se esta usando el modulo tarjeta CP2102 USB-Serial. Los controladores de este modulo pueden
 	 	 	 	descargarse de https://www.sparkfun.com/products/198, los controladores de la CP2102 USB-Serial vienen incluidos en en el
 	 	 	 	kernel de linux Versión 3.6.6.
*/

#ifndef MD49_H_
#define MD49_H_


/** API DE FUNCIONES */

/**
 @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
 @param fd Número del puerto de comunicación.
 @param Velocidad puntero a la direccion de memoria donde se encuentra el valor de la velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
		-2 Error no se logro leer los datos de el registro de velocidad 1.
*/
int obtenerVelocidad1(int fd, double *velocidad);


/**
 @brief Obtiene el valor del registro de velocidad 2 del MD49 y actualiza su valor.
 @param fd Número del puerto de comunicación.
 @param velocidad Puntero a la dirección de memoria donde se encuentra el valor de la velocidad 2.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 2.
		-2 Error no se logro leer los datos de el registro de velocidad 2.
*/
int obtenerVelocidad2(int fd, double *velocidad);

/**
 @brief Actualiza el contador del codificador de posición correspondiente al motor 1.
 @param fd Número del puerto de comunicación.
 @param codificadorPosicion1 Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 1.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor codificador 1.
		-2 Error no se pudieron leer los datos de los registro del codificador 1.
*/
int obtenerCodificadorMotor1(int fd, int *codificadorPosicion1);

/**
 @brief Actualiza el contador del codificador de posición correspondiente al motor 2.
 @param fd Número del puerto de comunicación.
 @param codificadorPosicion2 Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 2.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor codificador 2.
		-2 Error no se pudieron leer los datos de los registro del codificador 2.
*/
int obtenerCodificadorMotor2(int fd, int *codificadorPosicion2);

/**
 @brief Actualiza el contador de los codificadores de posición correspondiente a los motores.
 @param fd Número del puerto de comunicación.
 @param codificadorPosicion1 Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 1.
 @param codificadorPosicion2 Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 2.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor de los codificadores.
		-2 Error no se pudieron leer los datos de los registro de los codificadores.
*/
int obtenerCodificadoresMotores(int fd, int *codificadorPosicion1, int *codificadorPosicion2);

/**
 @brief Actualiza el valor del voltaje de la bateria que alimenta la MD49.
 @param fd Número del puerto de comunicación.
 @param voltajeBateria Puntero a la dirección de memoria donde se encuentra el valor del voltaje de la bateria que alimenta la MD49.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor del voltaje.
		-2 Error no se pudieron leer los datos de los registro del voltaje.
*/
int obtenerVolajeBateria(int fd, double *voltajeBateria);

/**
 @brief Actualiza el valor de la corriente consumida por el motor 1.
 @param fd Número del puerto de comunicación.
 @param corriente Puntero a la dirección de memoria donde se encuentra el valor de la corriente consumida por el motor 1.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 1.
		-2 Error no se pudieron leer los datos de los registro de corriente del motor 1.
*/
int obtenerCorrienteMotor1(int fd, double *corrienteMotor1);

/**
 @brief Actualiza el valor de la corriente consumida por el motor 2.
 @param fd Número del puerto de comunicación.
 @param corriente Puntero a la dirección de memoria donde se encuentra el valor de la corriente consumida por el motor 2.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 2.
		-2 Error no se pudieron leer los datos de los registro de corriente del motor 2.
*/
int obtenerCorrienteMotor2(int fd, double *corrienteMotor2);

/**
 @brief Actualiza el número de la versión del software del controlador MD49.
 @param fd Número del puerto de comunicación.
 @param versionSoftware Puntero a la dirección de memoria donde se encuentra la versión del software del controlador MD49.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura de la versión del software.
		-2 Error no se pudo leer el registro que contiene la versión del software.
*/
int obtenerNumeroVersion(int fd, double *versionSoftware);

/**
 @brief Actualiza el modo de aceleración en que trabaja la controladora.
 @param fd Número de puerto de comunicación.
 @param modoAceleracion Puntero a la dirección de memoria donde se encuentra el modo de aceleración actual.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del modo de aceleración.
		-2 Error no se pudo leer el registro que contiene el modo de aceleración.
*/
int obtenerModoAceleracion(int fd, int *modoAceleracion);

/**
 @brief Actualiza el modo de velocidad en que trabaja la controladora.
 @param fd Número de puerto de comunicación.
 @param modo Puntero a la dirección de memoria donde se encuentra el modo de velocidad actual.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del modo de velocidad.
		-2 Error no se pudo leer el registro que contiene el modo de velocidad.
*/
int obtenerModoVelocidad(int fd, int *modoVelocidad);

/**
 @brief Actualiza los datos de energia, voltaje de la Bateria, corriente motor 1 y corriente motor 2.
 @param fd Número de puerto de comunicación.
 @param voltaje Puntero a la dirección de memoria donde se encuentra el valor del voltaje de la bateria que alimenta la MD49.
 @param corrienteMotor1 Puntero a la dirección de memoria donde se encuentra el valor de la corriente consumida por el motor 1.
 @param corrienteMotor2 Puntero a la dirección de memoria donde se encuentra el valor de la corriente consumida por el motor 2.
 @return 0 operacion exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura de los datos de energia.
		-2 Error no se pudo leer los registros que contienen los datos de energia.
*/
int obtenerDatosEnergia(int fd, int *voltaje, int *corrienteMotor1, int *corrienteMotor2);

/**
 @brief Actualiza el estado del manejador de errores de la MD49.
 @param fd Número de puerto de comunicación.
 @param error Puntero a la dirección de memoria donde se encuentra el estado del manejador de errores de la MD49.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al enviar la solicitud de lectura del registro que almacena el estado del manejador de errores de la MD49.
		-2 Error no se pudo leer el registro que almacena el estado del manejador de errores de la MD49.
*/
int obtenerError(int fd, int *error);

/**
 @brief Establece un nuevo valor a el registro de velocidad 1 del controlador MD49.
 @param fd Número del puerto de comunicación.
 @param velocidad Nuevo valor de velocidad que se establecera al registro de velocidad 1.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir los datos en el registro de velocidad 1.
		-2 Error la escritura del registro velocidad 1 no fue correcta.
*/
int asignarVelocidad1(int fd, double velocidad);

/**
 @brief Establece un nuevo valor a el registro de velocidad 2 del controlador MD49.
 @param fd Número del puerto de comunicación.
 @param velocidad Nuevo valor de velocidad que se establecera al registro de velocidad 2.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir los datos en el registro de velocidad 2.
		-2 Error la escritura del registro velocidad 2 no fue correcta.
*/
int asignarVelocidad2(int fd, double velocidad);

/**
 @brief Establece un nuevo modo de aceleración a la controladora MD49.
 @param fd Número de puerto de comunicación.
 @param modoAceleracion Nuevo modo de aceleración.
 @return 0 Operación exitosa en caso contrario.
		-1 Error al intentar escribir los datos del registro modo aceleración.
		-2 Error la escritura del registro modo aceleración no fue correcta.
*/
int asignarModoAceleracion(int fd, int modoAceleracion);

/**
 @brief Establece un nuevo modo de velocidad de la controladora MD49.
 @param fd Número de puerto de comunicación.
 @param modoVelocidad Nuevo modo de velocidad.
 @return 0 Operacion exitosa en caso contrario.
		-1 Error al intentar escribir los datos del registro modo velocidad.
		-2 Error la escritura del registro modo velocidad no fue correcta.
*/
int asignarModoVelocidad(int fd, int modoVelocidad);

/**
 @brief Coloca en cero "0" los registros que almacenan los contadores de los codificados en la MD49.
 @param fd Número de puerto de comunicación.
 @return 0 Operacion exitosa en caso contrario.
 	 	-1 Ocurrio un error al ejecutar el comando.
*/
int reinicializarCodificadores(int fd);

/**
 @brief Activa la función de retroalimentación de los encoder.
 @param fd Número de puerto de comunicación.
 @return 0 Operacion exitosa en caso contrario.
		-1 Ocurrio un error al ejecutar el comando.
*/
int activarRetroalimentacionCodificadores(int fd);

/**
 @brief Desactiva la función de retroalimentación de los encoder.
 @param fd Número de puerto de comunicación.
 @return 0 Operacion exitosa en caso contrario.
		-1 Ocurrio un error al ejecutar el comando.
*/
int desactivarRetroalimentacionCodificadores(int fd);

/**
 @brief Activa la función de tiempo de seguridad (La MD49 deja de enviar ordenes a los motores si tiene 2 segundos sin comunicación).
 @param fd Número de puerto de comunicación.
 @return 0 Operacion exitosa en caso contrario.
		-1 Ocurrio un error al ejecutar el comando.
*/
int activarTiempoSeguridad(int fd);

/**
 @brief Desactiva la función de tiempo de seguridad.
 @param fd Número de puerto de comunicación.
 @return 0 Operacion exitosa en caso contrario.
		-1 Ocurrio un error al ejecutar el comando.
*/
int desactivarTiempoSeguridad(int fd);


/***********************************************************************/


#endif /* MD49_H_ */
