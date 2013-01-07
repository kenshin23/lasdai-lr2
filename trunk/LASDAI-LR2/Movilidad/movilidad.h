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
 @file movilidad.h
 @brief Declaración de todos los métodos de movilidad de la plataforma, esta libreria pertenece a la herramienta de
		desarrollo de la plataforma LASDAI LR2, brinda todos los métodos de movilidad al usuario para el desarrollo
		de sus aplicaciones, usa los driver de los motores implementado en la capa manejadores.
 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

 Algunos datos: Algunos de los parámetros de esta libreria manipulan información especifica de la plataforma, como la
 	 	 	 	distancia entre los puntos de contacto de las ruedas, la resolución del encoders de los motores y otros,
 	 			estos parámetros se configuran en el archivo de configuración de la libreria "definicion.h".

*/

#ifndef MOVILIDAD_H_
#define MOVILIDAD_H_

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include "../MD49/md49.h"
#include "definicionMovilidad.h"

/** @struct datosCinematica
 *  @brief Estructura que contiene los datos de la cinemática de la plataforma, posición y orientación en el plano cartesiano.
 *  @var datosCinematica::X
 *  Member 'x' Almacena la coordenada del robot en el eje de las abscisas (cm).
 *  @var datosCinematica::Y
 *  Member 'y' Almacena la coordenada del robot en el eje de las ordenadas (cm).
 *  @var datosCinematica::teta
 *  Member 'teta' Almacena el ángulo que representa la orientación de la plataforma (rad).
 */
struct datosCinematica {
	double x; /**< Posición en el eje x. */
	double y; /**< Posición en el eje y. */
	double theta; /**< Orientación de la plataforma. */
};

struct datosCinematica estadoActual;

/**
 @brief Inicializa el driver de la controladora de motores y los datos de la cinemática.
 @return 0 Operación exitosa en caso contrario.
 	 	-1 Error: No se pudo inicializar la comunicación con la controladora de motores.
		-2 Error: No se logro inicializar los parámetros en la controladora de motores.
*/
int inicializarMovilidad();

/**
 @brief Asigna una velocidad lineal y velocidad angular a la plataforma.
 @param	v Velocidad Lineal en cm/seg.
 @param w Velocidad Angular en rad/seg.
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No se pudo asignar la velocidad.
*/
int asignarVelocidad(double v, double w);

/**
 @brief Recorre una distancia d (cm) en línea recta (Hace uso de los encoders).
 @param d Distancia a recorrer en (cm).
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No se realizo el movimiento de forma correcta..
*/
int moverLineaRecta(double d);

/**
 @brief Gira la plataforma sobre su propio eje en los grados indicados (Hace uso de los encoders).
 @param theta Grados a girar en (rad).
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No se realizo el movimiento de forma correcta.
*/
int giroRelativo(double theta);

/**
 @brief Traslada de la posición actual a un punto indicado en el plano (x,y) con orientación theta,
 	 	actualiza el estado de la posición actual.
 @param estadoNuevo Estructura que contiene los datos de la posición deseada coordenada (x,y) cm y la orientación (theta).
 @return 0 Operación exitosa en caso contrario.
		-1 Error:  No se logro ir a la posicion (x,y,theta).
*/
int gotoXY(struct datosCinematica estadoNuevo);

/**
 @brief Realiza un diagnostico de la operatividad de la controladora de motores,
 	 	verifica la comunicación y el registro de errores de la controladora.
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No se pudo realizar el diagnostico.
		-2 Error: La controladora de motores no esta operativa, esta emitiendo un error.
*/
int diagnosticoOperatividadMovilidad();

/**
 @brief Actualiza el estado de la posición actual.
 @param estadoNuevo Estructura que contiene los datos a actualizar, coordenada (x,y) cm y la orientación (theta).

*/
void asignarDatosCinematica(struct datosCinematica estadoNuevo);

/**
 @brief Retorna los datos de la cinemática de la plataforma en un instante dado.
 @return 0 Operación exitosa en caso contrario.
*/
struct datosCinematica obtenerDatosCinematica();

/**
 @brief Calcula el numero de pulsos de encoders para una distancia d en cm.
 @param	d Distancia a recorrer en cm.
 @return pulsos Variable entera que contiene el numero de pulsos de encoders para una distancia d.
*/
int calculoNumeroPulsos(double d);

/**
 @brief Calcula el numero de cambios de velocidad para la rampa de aceleración implementadas en los métodos moverLineaRecta y giroRelativo.
 	 	los cambios dependen de la distancia a recorrer.
 @param distancia Distancia a recorrer en cm.
 @return cambios Número de cambios de velocidad en la rampa para la distancia indicada.
*/
int calculoCambios(int distancia);

/**
 @brief Valida el ángulo de giro, si el ángulo de giro es mayor a 180 entonces es mas óptimo realizar un giro negativo,
 	 	este método realiza el calculo del ángulo a girar para quedar en la posición deseada realizado un giro mas óptimo.
 @param	theta Ángulo de giro indicado.
 @return theta Ángulo de giro óptimo calculado.
*/
double calcularAnguloGiroRelativo(double theta);

/**
 @brief	Calcula el ángulo de orientación que debe tener la plataforma para trasladarse de un punto a otro.
 @param	distancia Distancia entre los dos puntos.
 @param catetoAdyacente Distancia en el eje x.
 @param	catetoOpuesto Distancia en le eje y.
 @return theta Ángulo calculado.
*/
double calculoAnguloGotoXY(double distancia, double catetoAdyacente, double catetoOpuesto);

/**
 @brief Termina la comunicación con la controlodaroa de motores.
 @return 0 Operación exitosa en caso contrario.
		-1 Error: No termino de forma correcta la comunicación con la controladora de motores.
*/
int terminarMovilidad();

#endif /* MOVILIDAD_H_ */
