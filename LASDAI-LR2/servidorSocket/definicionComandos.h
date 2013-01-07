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
 @file   definicionComandos.h
 @brief  Definición de las variables y comandos utilizadas por las rutinas de manejo de comandos.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

/** Activación del modo depuración para las rutinas de manejo de comandos **/
#define COMANDO_DEBUG

/** Comando para asignar velocidad lineal y velocidad angular a la plataforma **/
#define COMANDO_ASIGNAR_VELOCIDAD 0X11

/** Comando para recorrer una distancia indicada en línea recata **/
#define COMANDO_MOVER_LINEA_RECTA 0x12

/** Comando para realizar un giro sobre su propio eje ángulo indicado **/
#define COMANDO_GIRO_RELATIVO 0x13

/** Comando moverse a un punto del plano cartesiano con la orientación deseada **/
#define COMANDO_GOTO_XY 0x14

/** Comando para diagnosticar la operatividad del subsistema de movilidad **/
#define COMANDO_DIAGNOSTICO_OPERATIVIDAD_MOVILIDAD 0x15

/** Comando para asignar datos de cinemática **/
#define COMANDO_ASIGNAR_DATOS_CINEMATICA 0x16

/** Comando para obtener datos de cinemática **/
#define COMANDO_OBTENER_DATOS_CINEMATICA 0x17

/** Comando para obtener el valor de medida de un sensor ultrasonido en especifico, usando el ID del US **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_US 0X21

/** Comando para obtener el valor de medida de un sensor infrarrojo en especifico, usando el ID del IR **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_IR 0X22

/** Comando para obtener la medida del sensor trasero en un ángulo especifico **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_US_TRASERO 0X23

/** Comando para obtener el valor de los 6 ultrasonidos de la parte frontal de la plataforma **/
#define COMANDO_OBTENER_BARRIDO_FRONTAL_US 0x24

/** Comando para obtener el valor de los 6 sensores infrarrojos de la parte frontal de la plataforma **/
#define COMANDO_OBTENER_BARRIDO_FRONTAL_IR 0x25

/** comando para obtener el valor del sensor trasero en 5 ángulos distintos 50,70,90,110,130**/
#define COMANDO_OBTENER_BARRIDO_TRASERO_US 0x26
