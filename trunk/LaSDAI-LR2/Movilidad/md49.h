///**
// @file md49.h
// @brief Declaración de constantes y api de funciones para el manejo de los motores EMG49 con reductora 49:1 y una controladora MD49.
// @date Junio, 2012
// @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
//
// Algunos datos: La controladora MD49 funciona bajo dos estandares de comunicación Serial. Permite el control de dos motores, y esta
// 	 	 	 	diseñada especialmente para el control de motores EMG49. Las declaración  de constantes y api de funciones desarrolladas
// 	 	 	 	a continuacion representan el control del la placa MD49 en lenguaje C con comunicacion serial, para la conexion de la
// 	 	 	 	placa con el computador se esta usando el modulo tarjeta CP2102 USB-Serial. Los controladores de este modulo pueden
// 	 	 	 	descargarse de https://www.sparkfun.com/products/198.
//*/
//
//#ifndef MD49_H_
//#define MD49_H_
//
///** DEFINICIONES */
//
///** Se envia en el bufer antes de cada comando. */
//#define  byteDeSincronizacion 0x00
//
///** COMANDOS */
//
///** Comando para obtener la velocidad actual del motor 1. */
//#define comandoObtenerVelocidad1 0x21
//
///** Comando para obtener la velocidad actual del motor 2. */
//#define comandoObtenerVelocidad2 0x22
//
///** Comando para obtener el contador del codificador del motor 1. */
//#define comandoObtenerCodificadorMotor1 0x23
//
///** Comando para obtener el contador del codificador del motor 2. */
//#define comandoObtenerCodificadorMotor2 0x24
//
///** Comando para obtener el contador de los codificadores de ambos motores. */
//#define comandoObtenerCodificadorMotores 0x25
//
///** Comando para obtener el de la bateria. */
//#define comandoObtenerVoltajeBateria 0x26
//
///** Comando para obtener la corriente consumida por el motor 1. */
//#define comandoObtenerCorrienteMotor1 0x27
//
///** Comando para obtener la corriente consumida por el motor 2. */
//#define comandoObtenerCorrienteMotor2 0x28
//
///** Comando para obtener la version del software de la MD49. */
//#define comandoObtenerVersionSoftware 0x29
//
///** Comando para obtener el nivel de aceleración actual. */
//#define comandoObtenerAceleracion 0x2A
//
///** Comando para obtener el nivel de aceleración actual. */
//#define comandoObtenerModo 0x2B
//
///** Comando para obtener el voltaje de la bateria y la la corriente consumida por cada motor. */
//#define comandoObtenerDatosPotencia 0x2C
//
///** Comando para obtener el error indicado por el manejador de errores de la MD49. */
//#define comandoObtenerError 0x2D
//
///** Comando para asignar la velocidad 1 la funcionalidad de este comando depende del modo en que se este trabajando*/
//#define comandoAsignarVelocidad1 0x31
//
///** Comando para asignar la velocidad 2 la funcionalidad de este comando depende del modo en que se este trabajando*/
//#define comandoAsignarVelocidad2 0x32
//
///** Comando para asignar la aceleración deseada */
//#define comandoAsignarAceleracion 0x33
//
///** Comando para selecionar el mode de trabajo deseado */
//#define comandoSeleccionarModo 0x34
//
///** Comando para reiniciar el contador de los codificadores de los motores */
//#define comandoReinicioContadorCodificador 0x35
//
///** Comando para desactivar la variación de la potencia de salida a través de la retroalimetación de los codificadores */
//#define comandoDesactivarRetroalimentacion 0x36
//
///** Comando para activar la variación de la potencia de salida a través de la retroalimetación de los codificadores */
//#define comandoActivarRetroalimentacion 0x37
//
///** Comando para desactivar el tiempo de seguridad que detiene la funcionalidad de la MD49 despues de 2 seg sin comunicación*/
//#define comandoDesactivarTiempoSeguridad 0x38
//
///** Comando para activar el tiempo de seguridad que detiene la funcionalidad de la MD49 despues de 2 seg sin comunicación*/
//#define comandoActivarTiempoSeguridad 0x39
//
//
///** API DE FUNCIONES */
//
///**
// @brief Obtiene el valor del registro de velocidad 1 del MD49 y actualiza el dato.
// @param fd número del puerto de comunicación.
// @param velocidad puntero a la direccion de memoria donde se encuentra el valor de la velocidad 1.
// @return 0 operación exitosa en caso contrario.
//		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 1.
//		-2 Error no se logro leer los datos de el registro de velocidad 1.
//*/
//int obtenerVelocidad1(int fd, double *velocidad);
//
//
///**
// @brief Obtiene el valor del registro de velocidad 2 del MD49 y actualiza su valor.
// @param fd número del puerto de comunicación.
// @param velocidad puntero a la direccion de memoria donde se encuentra el valor de la velocidad 2.
// @return 0 operación exitosa en caso contrario.
//		-1 Error al enviar la solicitud de lectura para valor del registro de velocidad 2.
//		-2 Error no se logro leer los datos de el registro de velocidad 2.
//*/
//int obtenerVelocidad2(int fd, double *velocidad);
//
//
//
//
//
//
//
//
//
//
///**
// @brief establece un nuevo valor a el registro de velocidad 1 del controlador.
// @param fd numero del puerto de comunicacion.
// @param velocidad nuevo valor de velocidad.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al intentar escribir los datos de velocidad 1.
//	-2 Error la escritura de la velocidad 1 no fue correcta.
//*/
//int asignarVelocidad1(int fd, double velocidad);
//
//
//
///**
// @brief establece un nuevo valor a el registro de velocidad 2 del controlador.
// @param fd numero de puerto de comunicacion.
// @param velocidad nuevo valor de velocidad.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al intentar escribir los datos de velocidad 2.
//	-2 Error la escritura de la velocidad 2 no fue correcta.
//*/
//int asignarVelocidad2(int fd, double velocidad);
//
//
//
///**
// @brief actualiza la posicion del condificador del motor 1.
// @param fd numero del puerto de comunicacion.
// @param posicion puntero a la direccion de memoria donde se encuentra el valor de la posicion del motor 1.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del valor codificador 1.
//	-2 Error no se pudieron leer los datos de los registro del codificador 1.
//*/
//int obtenerCodificadorMotor1(int fd, int *posicion);
//
///**
// @brief actualiza la posicion del condificador del motor 2.
// @param fd numero del puerto de comunicacion.
// @param posicion puntero a la direccion de memoria donde se encuentra el valor de la posicion del motor 2.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del valor codificador 2.
//	-2 Error no se pudieron leer los datos de los registro del codificador 2.
//*/
//int obtenerCodificadorMotor2(int fd, int *posicion);
//
///**
// @brief actualiza el valor del voltaje de la bateria.
// @param fd numero del puerto de comunicacion.
// @param voltaje puntero a la direccion de memoria donde se encuentra el valor del voltaje.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del valor del voltaje.
//	-2 Error no se pudieron leer los datos de los registro del voltaje.
//*/
//int obtenerVolajeBateria(int fd, double *voltaje);
//
///**
// @brief actualiza el valor de la corriente suministrada al motor 1.
// @param fd numero del puerto de comunicacion.
// @param corriente puntero a la direccion de memoria donde se encuentra el valor de la corriente suministrada al motor 1.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 1.
//	-2 Error no se pudieron leer los datos de los registro de corriente del motor 1.
//*/
//int obtenerCorrienteMotor1(int fd, double *corriente);
//
///**
// @brief actualiza el valor de la corriente suministrada al motor 2.
// @param fd numero del puerto de comunicacion.
// @param corriente puntero a la direccion de memoria donde se encuentra el valor de la corriente suministrada al motor 2.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del valor de la corriente del motor 2.
//	-2 Error no se pudieron leer los datos de los registro de corriente del motor 2.
//*/
//int obtenerCorrienteMotor2(int fd, double *corriente);
//
///**
// @brief actualiza el numero de la vercion del software del controlador.
// @param fd numero del puerto de comunicacion.
// @param vercion puntero a la direccion de memoria donde se encuentra la vercion del software.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura de la version del software.
//	-2 Error no se pudo leer el registro que contiene la version del software.
//*/
//int obtenerNumeroVersion(int fd, double *version);
//
///**
// @brief establece un nuevo mode de aceleracion a la controladora.
// @param fd numero de puerto de comunicacion.
// @param modo nuevo modo de aceleracion.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al intentar escribir los datos del registro modo aceleracion.
//	-2 Error la escritura del registro modo aceleracion no fue correcta.
//*/
//int asignarModoAceleracion(int fd, int modo);
//
///**
// @brief actualiza el modo de aceleracion en que trabaja la controladora.
// @param fd numero de puerto de comunicacion.
// @param modo puntero a la direccion de memoria donde se encuentra el modo de aceleracion actual.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del modo de aceleracion.
//	-2 Error no se pudo leer el registro que contiene el modo de aceleracion.
//*/
//int obtenerModoAceleracion(int fd, int *modoAceleracion);
//
///**
// @brief establece un nuevo mode de velocidad de la controladora.
// @param fd numero de puerto de comunicacion.
// @param modo nuevo modo de velocidad.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al intentar escribir los datos del registro modo velocidad.
//	-2 Error la escritura del registro modo velocidad no fue correcta.
//*/
//int asignarModoVelocidad(int fd, int modoVelocidad);
//
///**
// @brief actualiza el modo de velocidad en que trabaja la controladora.
// @param fd numero de puerto de comunicacion.
// @param modo puntero a la direccion de memoria donde se encuentra el modo de velocidad actual.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al enviar la solicitud de lectura del modo de velocidad.
//	-2 Error no se pudo leer el registro que contiene el modo de velocidad.
//*/
//int obtenerModoVelocidad(int fd, int *modoVelocidad);
//
///**
// @brief enviar un comando a la controladora.
// @param fd numero de puerto de comunicacion.
// @param comando comando a enviar a la controladora.
// @return 0 operacion exitosa en caso contrario.
//	-1 Error al intentar enviar un comando.
//	-2 Error el comando no fue enviado con exito.
//*/
//int enviarComando(int fd, unsigned char comando);
//
///***********************************************************************/
//
//
//#endif /* MD49_H_ */
