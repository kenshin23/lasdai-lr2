/********************************************************************************
* This program is free software; you can redistribute it and/or modify it under *
* the terms of the GNU General Public License as published by the Free Software *
* Foundation; either version 2 of the License, or (at your option) any later 	*
* version. This program is distributed in the hope that it will be useful, but 	*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more *
* details. You should have received a copy of the GNU General Public License 	*
* along with this program; if not, write to the Free Software Foundation, Inc., *
* 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.						*
* (c) Copyright 2012 José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.	*				*
********************************************************************************/

/**
 @file serial.h
 @brief Declaración de constantes y api de funciones para el manejo de puerto serial.
 @date Junio, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include "definicionSerial.h"

/**
 @brief	Apertura del puerto de comunicación serial.
 @param fd Puntero a la dirección de memoria de la variable entera que almacena el número "ID" del puerto.
 @param tty Variable char* que almacena el nombre del puerto que se desea abrir.
 @param baudios Variable char* que almacena la velocidad en de la comunicación en Baudios. Eje "B19200".
 @return 0 operación exitosa en caso contrario.
		-1 Error: No se logro abrir el puerto de comunicación con el dispositivo.
*/
int abrirPuertoPercepcion(int *fd);

int abrirPuertoMD49(int *fd);

/**
 @brief Escribir datos por el puerto serial.
 @param fd Número del puerto de comunicación.
 @param nBytes Número de datos a escribir.
 @param sbuf Puntero a la dirección de memoria del buffer que contiene los datos a escribir.
 @return 0 Operación exitosa en caso contrario.
		-1 Error no se lograron escribir los datos.
		-2 Error solo se escribieron #bytes de #nBytes.
*/
int escribirDatos(int fd, int nBytes, unsigned char* sbuf);

/**
 @brief Leer datos por el puerto serial.
 @param fd Número del puerto de comunicación.
 @param nBytes Número de datos a leer.
 @param sbuf Puntero a la dirección de memoria del buffer donde se almacenaran los datos a leer.
 @return 0 Operación exitosa en caso contrario.
	-1 Error no se logro leer los datos.
	-2 Error solo se logro leer #bytes de #nBytes.
*/
int leerDatos(int fd, int nBytes, unsigned char* sbuf);

/**
 @brief Verifica si existen datos en el bufer serial.
 @param fd Número del puerto de comunicación.
 @param nBytes Puntero a la direccion de memoria que almacena el numero de bytes que hay en el bufer.
 @return 1 Hay bytes en bufer coloca el numero de bytes encontrados en nBytes.
		 0 No hay nada en el bufer serial
		-1 Error no se logro censar el bufer serial.
*/
int verificarBufer(int fd, int *nBytes);

/**
 @brief Clausura del puerto de comunicación serial.
 @param fd Variable entera que almacena el número del puerto de comunicación .
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No se logro cerrar el puerto de comunicación con el dispositivo.
*/
int cerrarPuerto(int fd);

#endif /* SERIAL_H_ */
