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
int diagnosticoOperatividad();

/**
 @brief Actualiza el estado de la posición actual.
 @param estadoNuevo Estructura que contiene los datos a actualizar, coordenada (x,y) cm y la orientación (theta).

*/
void asignarDatosCinematica(struct datosCinematica estadoNuevo);

/**
 @brief .
 @return 0 Operación exitosa en caso contrario.
*/
struct datosCinematica obtenerDatosCinematica();

/**
 @brief .
 @param
 @return 0 Operación exitosa en caso contrario.
		-1 Error: .
		-2 Error: .
*/
int calculoNumeroPulsos(double d);

/**
 @brief .
 @param
 @return 0 Operación exitosa en caso contrario.
		-1 Error: .
		-2 Error: .
*/
int calculoCambios(int distancia);

/**
 @brief .
 @param
 @return 0 Operación exitosa en caso contrario.
		-1 Error: .
		-2 Error: .
*/
double calcularAnguloGiroRelativo(double theta);

/**
 @brief .
 @param
 @return 0 Operación exitosa en caso contrario.
		-1 Error: .
		-2 Error: .
*/
int terminarMovilidad();

#endif /* MOVILIDAD_H_ */
