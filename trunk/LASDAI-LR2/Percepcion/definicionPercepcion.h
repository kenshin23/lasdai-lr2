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
 @file   definicionPercepcion.h
 @brief  Definición de las variables y comando utilizadas por las rutinas de manipulación del sistema de percepción.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

/** DEFINICIONES DEL SISTEMA DE PERCEPCION **/

/** Activación del modo depuración para las rutinas del sistema de percepción  **/
#define PERCEPCION_DEBUG

/** Puerto de Trabajo del la comunicación serial con la manejadora del sistema de percepción tty **/
#define TTY_PERCEPCION "/dev/Arduino"

/** Velocidad de trabajo de la comunicación Serial para la comunicación con la manejadora del sistema de percepción **/
#define BAUDIOS_PERCEPCION 9600

/** Tiempo de retraso para esperar respuesta del sistema de percepción después de escribir un comando (microsegundos) **/
#define RETRASO 95000

/** Se enviá en el bufer antes de cada comando. */
#define  BYTE_SINCRONIZACION 0x00

/** Se enviá en el bufer al final de cada comando. */
#define  BYTE_FIN_COMANDO 0xFF

/** COMANDOS DEL SISTEMA DE PERCEPCION **/

/** Comando para obtener la medida de un sensor US (Argumento id del sensor)*/
#define OBTENER_MEDIDA_US 0X11

/** Comando para obtener la medida de un sensor IR (Argumento id del sensor)*/
#define OBTENER_MEDIDA_IR 0X12

/** Comando para obtener la medida del sensor US trasero en determinado angulo (Argumento angulo de la lectura)*/
#define OBTENER_MEDIDA_UST 0X13

/** Comando para obtener un barrido del anillo frontal de US */
#define	OBTENER_BARRIDO_FRONTAL_US 0X14

/** Comando para obtener un barrido del anillo frontal de IR */
#define	OBTENER_BARRIDO_FRONTAL_IR 0X15

/** Comando para obtener un barrido del US trasero cada 20 grados */
#define OBTENER_BARRIDO_TRASERO 0X16

