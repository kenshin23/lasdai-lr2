/**
 @file motores.h
 @brief Declaración de contantes y api de funciones para el manejo de los motores EMG30 con reductora 36:1 utilizando una controladora MD25 y ruedas S360182.
 @date Agosors, 2011.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com

 Algunos datos: Velocidad maxima del motor 7200 rpm, con la reductora de 36:1 queda en 200 rpm en el eje,  a segundos es 3.333 rps.
 El diametro de la ruedas es 0.1 mts, lo que implica que la velocidad maxima es (0.05mts*PI*2)*(0.333 rev/seg)= 1.047197 mts/seg.
*/


#ifndef MOVILIDAD_H_
#define MOVILIDAD_H_

struct datosCinematica {
	double x; //posicion en el eje x.
	double y; //posicion en el eje y.
	double teta; //orientacion del robot.
};

/**
 @brief Inicializa la comunicacion con los motores y configura los modos de trabajo.
 @param fd puntero a la direcciones de memoria a la variable que almacena el numero del puerto.
 @return 0 operacion exitosa en caso contrario.
	-1 Error: No se logro iniciar la comunicacion con los motores.
	-2 Error: No se logro insertar la configuracion de trabajo de los motores.
*/
int iniciarComunicacionMotores(int *fd);

/**
 @brief Asigana la velodidad lineal a los motores.
 @param fd numero del puerto de comunicacion.
 @param vl valor de la valeocidad linal en (mts/seg). En un rango (+ adelante/- atras)[0,008-1,016](mts/seg).
 @return 0 operacion exitosa en caso contrario.
	-1 Error: No se logro obtener el valor de la velocidad lineal.
*/
int asignarVelocidadLineal(int fd, double vl);

/**
 @brief Actualiza el valor de la velocidad lineal.
 @param fd numero del puerto de comunicacion.
 @param vl puntero al la variable que almacena el valor de la valeocidad linal en (mts/seg).
 @return 0 operacion exitosa en caso contrario.
	-1 Error: No se logro asignar la velocidad lineal.
*/
int obtenerVelocidadLineal(int fd, double *vl);

/**
 @brief Asigana la velodidad angular a los motores.
 @param fd numero del puerto de comunicacion.
 @param w valor de la valeocidad angular en (rad/seg). En un rango de (+ derecha /- izquierda)[0,061-7,69](rad/seg) .
 @return 0 operacion exitosa en caso contrario.
	-1 Error: No se logro asignar la velocidad angular.
*/
int asignarVelocidadAngular(int fd, double w);

/**
 @brief Actualiza el valor de la velocidad angular.
 @param fd numero del puerto de comunicacion.
 @param w puntero al la variable que almacena el valor de la valeocidad angular en (rad/seg).
 @return 0 operacion exitosa en caso contrario.
        -1 Error: No se logro asignar la velocidad angular.
*/
int obtenerVelocidadAngular(int fd, double *w);

/**
 @brief Recorre una distancia (mts) en linea recta.
 @param fd numero del puerto de comunicacion.
 @param vl velocidad lineal con que se realizara el recorrido (mts/seg).
 @return 0 operacion exitosa en caso contrario.
        -1 Error: No se logro realizar el movimiento.
*/
int moverLineaRecta(int fd, double d, double vl);

/**
 @brief Actualiza el valor de la velocidad angular.
 @param fd numero del puerto de comunicacion.
 @param w velocidad angular con que se realizara el recorrido (rad/seg).
 @return 0 operacion exitosa en caso contrario.
       -1 Error:  No se logro realizar el giro.
*/
int girar(int fd, double teta, double w);

/**
 @brief Traslada de la posicion actual a un punto indicado en el plano (x,y) con orientacion teta.
 @param fd numero del puerto de comunicacion.
 @param estadoActual puntero a direcion de memorida de la estructura que contiene los datos actuales de cinematica del robot (Posicion y Orientacion).
 @param estadoNuevo estructura que contiene los nuevos datos de cinematica del robot (Posicion y Orientacion).
 @return 0 operacion exitosa en caso contrario.
        -1 Error:  No se logro ir a la posicion (x,y,teta) solicitada.
*/
int gotoXY(int fd, struct datosCinematica *estadoActual, struct datosCinematica estadoNuevo);

/**
 @brief Calcula el angulo teta que representa la orientacion que se debe tomar para trasladarce al punto (x,y).
 @param fd numero del puerto de comunicacion.
 @param teta direccion del vector de tralacion (x,y).
 @param x componente en el eje x del vectror de traslacion.
 @param y componente en el eje y del vectror de traslacion.
 @return 0 operacion exitosa en caso contrario.
        -1 Error:  No se logro ir a la posicion (x,y,teta) solicitada.
*/
double calculoCuadrante(double teta, double x, double y);

/**
 @brief Calcula el factor de conversion entre pulsos del codificador y recorrido del la ruedas.
  @return 0 operacion exitosa en caso contrario.
	 -1 La comunicacion no se termino con exito.
*/
int terminarComunicacionMotores(int fd);

/**
 @brief Calcula el factor de conversion entre pulsos del codificador y recorrido del la ruedas.
 @param d distancia a recorrer por el motor.
 @return pulsos numero de pulsos a del codificador para que el motor recorra esa distancia.
*/
int numeroPulsos(double d);

/**
 @brief Calcula el teta para un giro optimo.
 @param teta valor del giro a relizar.
 @return teta valor del giro optimo.
*/
double calcularTeta(double teta);

#endif /* MOVILIDAD_H_ */
