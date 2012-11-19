///**
// @file serial.h
// @brief Declaración de constantes y api de funciones para el manejo de puerto serial.
// @date Junio, 2012
// @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
//*/
//
//#ifndef SERIAL_H_
//#define SERIAL_H_
//
///**
// @brief	Apertura del puerto de comunicación serial.
// @param fd Puntero a la dirección de memoria de la variable entera que almacena el número del puerto.
// @param tty Variable char* que almacena el nombre del puerto que se desea abrir.
// @param baudios Variable char* que almacena la velocidad en baudios en que va a trabajar la comunicación. Eje "B19200".
// @return 0 operación exitosa en caso contrario.
//		-1 Error: No se logro abrir el puerto de comunicación con el dispositivo.
//*/
//int abrirPuerto(int *fd, char* tty, char* baudios);
//
///**
// @brief Clausura del puerto de comunicación serial.
// @param fd Variable entera que almacena el número del puerto de comunicación .
// @return 0 Operación exitosa en caso contrario.
//		-1 Error: No se logro cerrar el puerto de comunicación con el dispositivo.
//*/
//int cerrarPuerto(int fd);
//
///**
// @brief Escribir datos por el puerto serial.
// @param fd Número del puerto de comunicación.
// @param nBytes Números de datos a escribir.
// @param sbuf Puntero a la dirección de memoria del buffer que contiene los datos a escribir.
// @return 0 Operación exitosa en caso contrario.
//		-1 Error no se lograron escribir los datos.
//		-2 Error solo se escribieron #bytes de #nBytes.
//*/
//int escribirDatos(int fd, int nBytes, unsigned char* sbuf);
//
///**
// @brief Leer datos por el puerto serial.
// @param fd Número del puerto de comunicación.
// @param nBytes Números de datos a leer.
// @param sbuf Puntero a la dirección de memoria del buffer donde se almacenaran los datos a leer.
// @return 0 Operación exitosa en caso contrario.
//	-1 Error no se logro leer los datos.
//	-2 Error solo se logro leer #bytes de #nBytes.
//*/
//int leerDatos(int fd, int nBytes, unsigned char* sbuf);
//
//
//
//#endif /* SERIAL_H_ */
