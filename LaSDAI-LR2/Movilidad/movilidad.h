/**
 @file movilidad.h
 @brief Declaración de todos los métodos de movilidad de la plataforma, esta libreria pertenece a la herramienta de
		desarrollo de la plataforma LASDAI LR2, brinda todos los métodos de movilidad al usuario para el desarrollo
		de sus aplicaciones, usa los driver de los motores implementado en la capa manejadores, esta libreria esta
		desacoplada del hardware.

 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com

 	 	Algunos datos: Algunos de los parámetros de esta libreria manipulan información especifica de la plataforma,
 	 	como la distancia entre los puntos de contacto de las ruedas, la resolución del encoders de los motores y otros
 	 	estos parámetros se configuran en el archivo de configuración de la libreria "definicion.h".

*/

#ifndef MOVILIDAD_H_
#define MOVILIDAD_H_

/** @struct datosCinematica
 *  @brief Estructura que contiene los datos de la cinemática de la plataforma, posición y orientación en el plano cartesiano.
 *  @var datosCinematica::X
 *  Member 'x' Almacena la coordenada del robot en el eje de las abscisas.
 *  @var datosCinematica::Y
 *  Member 'y' Almacena la coordenada del robot en el eje de las ordenadas.
 *  @var datosCinematica::teta
 *  Member 'teta' Almacena el ángulo que representa la orientación de la plataforma.
 */
struct datosCinematica {
	double x; /**< Posición en el eje x. */
	double y; /**< Posición en el eje y. */
	double teta; /**< Orientación de la plataforma. */
};

struct datosCinematica estadoActual;

/**
 @brief Carga y configura el driver de los motores e inicializa los parámetros de cinemática de la plataforma.
 @return 0 operacion exitosa en caso contrario.
	-1 Error: .
	-2 Error: .
*/
int inicializarMovilidad();

int asignarVelocidad(double v, double w);

int moverLineaRecta(double d);

int giroRelativo(double teta);

int gotoXY(struct datosCinematica estadoNuevo);

int diagnosticoOperatividad();

void asignarDatosCinematica(struct datosCinematica estadoNuevo);

void obtenerDatosCinematica(struct datosCinematica *estado);

int calculoNumeroPulsos(double d);

int calculoVelecidad(int rampa, int codificador1, int codificador2, int pulsos);

int terminarMovilidad();

#endif /* MOVILIDAD_H_ */
