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
 @file   definicionMD49.h
 @brief  Definición de las variables y comandos utilizadas por las rutinas de manipulación de la tarjeta controladora de motores MD49.
 @date   Octubre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

/** DEFINICIONES MD49*/

/** Activación del modo depuración para las rutinas de MD49 **/
#define MD49_DEBUG

/** Puerto de Trabajo del la comunicación serial con la MD49 tty **/
#define TTY_MD49 "/dev/ttyUSB0"

/** Velocidad de trabajo de la comunicación Serial con la MD49 **/
#define BAUDIOS_MD49 38400

/** Tiempo de retraso para esperar respuesta de la MD49 después de escribir **/
#define RETRASO 7800

/** Se enviá en el bufer antes de cada comando. */
#define  BYTE_SINCRONIZACION 0x00

/** COMANDOS */

/** Comando para obtener la velocidad actual del motor 1. */
#define COMANDO_OBTENER_VELOCIDAD_1 0x21

/** Comando para obtener la velocidad actual del motor 2. */
#define COMANDO_OBTENER_VELOCIDAD_2 0x22

/** Comando para obtener el contador del codificador del motor 1. */
#define COMANDO_OBTENER_CODIFICADOR_MOTOR_1 0x23

/** Comando para obtener el contador del codificador del motor 2. */
#define COMANDO_OBTENER_CODIFICADOR_MOTOR_2 0x24

/** Comando para obtener el contador de los codificadores de ambos motores. */
#define COMANDO_OBTENER_CODIFICADOR_MOTORES 0x25

/** Comando para obtener el Voltaje de la batería que alimenta la MD49. */
#define COMANDO_OBTENER_VOLTAJE_BATERIA 0x26

/** Comando para obtener la corriente consumida por el motor 1. */
#define COMANDO_OBTENER_CORRIENTE_MOTOR_1 0x27

/** Comando para obtener la corriente consumida por el motor 2. */
#define COMANDO_OBTENER_CORRIENTE_MOTOR_2 0x28

/** Comando para obtener la version del software de la MD49. */
#define COMANDO_OBTENER_VERSION_SOFTWARE 0x29

/** Comando para obtener el nivel de aceleración actual. */
#define COMANDO_OBTENER_MODO_ACELERACION 0x2A

/** Comando para obtener el modo de velocidad actual. */
#define COMANDO_OBTENER_MODO_VELOCIDAD 0x2B

/** Comando para obtener el voltaje de la batería y la la corriente consumida por cada motor. */
#define COMANDO_OBTENER_DATOS_ENERGIA 0x2C

/** Comando para obtener el error indicado por el manejador de errores de la MD49. */
#define COMANDO_OBTENER_ERROR 0x2D

/** Comando para asignar la velocidad 1 la funcionalidad de este comando depende del modo en que se este trabajando*/
#define COMANDO_ASIGNAR_VELOCIDAD_1 0x31

/** Comando para asignar la velocidad 2 la funcionalidad de este comando depende del modo en que se este trabajando*/
#define COMANDO_ASIGNAR_VELOCIDAD_2 0x32

/** Comando para asignar la aceleración deseada */
#define COMANDO_ASIGNAR_MODO_ACELERACION 0x33

/** Comando para seleccionar el mode de trabajo deseado */
#define COMANDO_ASIGNAR_MODO_VELOCIAD 0x34

/** Comando para reiniciar el contador de los codificadores de los motores */
#define COMANDO_REINICIO_CONTADOR_CODIFICADOR 0x35

/** Comando para desactivar la variación de la potencia de salida a través de la retroalimentación de los codificadores */
#define COMANDO_DESACTIVAR_RETROALIMENTACION 0x36

/** Comando para activar la variación de la potencia de salida a través de la retroalimentación de los codificadores */
#define COMANDO_ACTIVAR_RETROALIMENTACION 0x37

/** Comando para desactivar el tiempo de seguridad que detiene la funcionalidad de la MD49 después de 2 seg sin comunicación*/
#define COMANDO_DESACTIVAR_TIEMPO_SEGURIDAD 0x38

/** Comando para activar el tiempo de seguridad que detiene la funcionalidad de la MD49 después de 2 seg sin comunicación*/
#define COMANDO_ACTIVAR_TIEMPO_SEGURIDAD 0x39

/** MANEJO DE ERRORES EN MD49 */

/** Este error es enviado por la MD49 si el voltaje de la batería ha caído por debajo del umbral de los 16V */
#define ERROR_BAJO_VOLTAJE 0b10000000

/** Este error es enviado por la MD49 si el voltaje de la batería supera el umbral de los 30V */
#define ERROR_ALTO_VOLTAJE 0b01000000

/** Este error es enviado por la MD49 si se detecta un corto en el motor 2 */
#define ERROR_CORTO_MOTOR_2 0b00100000

/** Este error es enviado por la MD49 si se detecta un corto en el motor 1 */
#define ERROR_CORTO_MOTOR_1 0b00010000

/** Este error es enviado por la MD49 si se detecta un consumo mayor a 10A por parte del motor 2 */
#define ERROR_CORRIENTE_MOTOR_2 0b00001000

/** Este error es enviado por la MD49 si se detecta un consumo mayor a 10A por parte del motor 1 */
#define ERROR_CORRIENTE_MOTOR_1 0b00000100
