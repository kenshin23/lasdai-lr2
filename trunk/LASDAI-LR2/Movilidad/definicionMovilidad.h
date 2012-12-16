/**
 @file   definicion.h
 @brief  Definición de las variables y comando utilizadas por las rutinas de manipulación del sistema de percepción.
 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

/** DEFINICIONES DE LA LIBRERIA DE MOVILIDAD **/

/** Modo de aceleración de la controladora de motores de 0 a 79,81(cm/seg) en 0,41(seg) **/
#define DEFAUL_ACELERACION_MODE 5

/** Modo de velocidad usado para la controladora de motores -128/0/128 **/
#define DEFAUL_VELOCIDAD_MODO 1

/** Distancia entre los puntos de contactos de las ruedas **/
#define LONGITUD_EJE 30

/** Diametro de las ruedas (cm)  **/
#define DIAMETRO_RUEDA 12,5

/**  Número de pulsos por revolución del motor **/
#define PULSOS_REVOLUCION 980

/** Modo de velocidad usado para la controladora de motores donde Velocidad 2 es la velocidad de giro **/
#define VELOCIDAD_MODO_GIRO 4

/** Velocidad 0 para detener la plataforma  **/
#define DETENER 0

/** Velocidad inicial de rampa de aceleración **/
#define VELOCIDAD_INICIAL_RAMPA 16

/** Pulsos de cambio de la rampa equivalen a 5 cm aproximadamente **/
#define PULSOS_DE_CAMBIOS_RAMPA 124

/** Retraso entre cada movimiento del método gotoXY (microsegundos) **/
#define RETARDO 500000

/** Activación del modo depuración de las rutinas de movilidad  **/
#define MOVILIDAD_DEBUG
