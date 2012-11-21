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
 @param codificadorPosicion Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 1.
 @return 0 Operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del valor codificador 1.
	-2 Error no se pudieron leer los datos de los registro del codificador 1.
*/
int obtenerCodificadorMotor1(int fd, int *codificadorPosicion);

/**
 @brief Actualiza el contador del codificador de posición correspondiente al motor 2.
 @param fd Número del puerto de comunicación.
 @param codificadorPosicion Puntero a la dirección de memoria donde se encuentra el valor del contador de posición del motor 2.
 @return 0 Operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del valor codificador 2.
	-2 Error no se pudieron leer los datos de los registro del codificador 2.
*/
int obtenerCodificadorMotor2(int fd, int *codificadorPosicion);

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
 @param voltaje Puntero a la dirección de memoria donde se encuentra el valor del voltaje de la bateria que alimenta la MD49.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del valor del voltaje.
	-2 Error no se pudieron leer los datos de los registro del voltaje.
*/
int obtenerVolajeBateria(int fd, double *voltaje);

/**
 @brief actualiza el valor de la corriente suministrada al motor 1.
 @param fd numero del puerto de comunicacion.
 @param corriente puntero a la direccion de memoria donde se encuentra el valor de la corriente suministrada al motor 1.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 1.
	-2 Error no se pudieron leer los datos de los registro de corriente del motor 1.
*/
int obtenerCorrienteMotor1(int fd, double *corriente);

/**
 @brief actualiza el valor de la corriente suministrada al motor 2.
 @param fd numero del puerto de comunicacion.
 @param corriente puntero a la direccion de memoria donde se encuentra el valor de la corriente suministrada al motor 2.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 2.
	-2 Error no se pudieron leer los datos de los registro de corriente del motor 2.
*/
int obtenerCorrienteMotor2(int fd, double *corriente);












/**
 @brief establece un nuevo valor a el registro de velocidad 1 del controlador.
 @param fd numero del puerto de comunicacion.
 @param velocidad nuevo valor de velocidad.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al intentar escribir los datos de velocidad 1.
	-2 Error la escritura de la velocidad 1 no fue correcta.
*/
int asignarVelocidad1(int fd, double velocidad);



/**
 @brief establece un nuevo valor a el registro de velocidad 2 del controlador.
 @param fd numero de puerto de comunicacion.
 @param velocidad nuevo valor de velocidad.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al intentar escribir los datos de velocidad 2.
	-2 Error la escritura de la velocidad 2 no fue correcta.
*/
int asignarVelocidad2(int fd, double velocidad);




/**
 @brief actualiza el numero de la vercion del software del controlador.
 @param fd numero del puerto de comunicacion.
 @param vercion puntero a la direccion de memoria donde se encuentra la vercion del software.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura de la version del software.
	-2 Error no se pudo leer el registro que contiene la version del software.
*/
int obtenerNumeroVersion(int fd, double *version);

/**
 @brief establece un nuevo mode de aceleracion a la controladora.
 @param fd numero de puerto de comunicacion.
 @param modo nuevo modo de aceleracion.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al intentar escribir los datos del registro modo aceleracion.
	-2 Error la escritura del registro modo aceleracion no fue correcta.
*/
int asignarModoAceleracion(int fd, int modo);

/**
 @brief actualiza el modo de aceleracion en que trabaja la controladora.
 @param fd numero de puerto de comunicacion.
 @param modo puntero a la direccion de memoria donde se encuentra el modo de aceleracion actual.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del modo de aceleracion.
	-2 Error no se pudo leer el registro que contiene el modo de aceleracion.
*/
int obtenerModoAceleracion(int fd, int *modoAceleracion);

/**
 @brief establece un nuevo mode de velocidad de la controladora.
 @param fd numero de puerto de comunicacion.
 @param modo nuevo modo de velocidad.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al intentar escribir los datos del registro modo velocidad.
	-2 Error la escritura del registro modo velocidad no fue correcta.
*/
int asignarModoVelocidad(int fd, int modoVelocidad);

/**
 @brief actualiza el modo de velocidad en que trabaja la controladora.
 @param fd numero de puerto de comunicacion.
 @param modo puntero a la direccion de memoria donde se encuentra el modo de velocidad actual.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al enviar la solicitud de lectura del modo de velocidad.
	-2 Error no se pudo leer el registro que contiene el modo de velocidad.
*/
int obtenerModoVelocidad(int fd, int *modoVelocidad);

/**
 @brief enviar un comando a la controladora.
 @param fd numero de puerto de comunicacion.
 @param comando comando a enviar a la controladora.
 @return 0 operacion exitosa en caso contrario.
	-1 Error al intentar enviar un comando.
	-2 Error el comando no fue enviado con exito.
*/
int enviarComando(int fd, unsigned char comando);

/***********************************************************************/


#endif /* MD49_H_ */
