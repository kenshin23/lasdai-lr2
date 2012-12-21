/**
 @file   definicionSocket.h
 @brief  Definición de las variables y comandos utilizadas por las rutinas de manejo del servidor socket.
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9
*/

/** Activación del modo depuración para las rutinas de manejo de comandos **/
#define COMANDO_DEBUG

/** **/
#define COMANDO_ASIGNAR_VELOCIDAD 0X11

/** **/
#define COMANDO_MOVER_LINEA_RECTA 0x12

/** **/
#define COMANDO_GIRO_RELATIVO 0x13

/** **/
#define COMANDO_GOTO_XY 0x14

/** **/
#define COMANDO_DIAGNOSTICO_OPERATIVIDAD 0x15

/** **/
#define COMANDO_ASIGNAR_DATOS_CINEMATICA 0x16

/** **/
#define COMANDO_OBTENER_DATOS_CINEMATICA 0x17

/** **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_US 0X21

/** **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_IR 0X22

/** **/
#define COMANDO_OBTENER_MEDIDA_SENSOR_US_TRASERO 0X23

/** **/
#define COMANDO_OBTENER_BARRIDO_FRONTAL_US 0x24

/** **/
#define COMANDO_OBTENER_BARRIDO_FRONTAL_IR 0x25

/** **/
#define COMANDO_OBTENER_BARRIDO_TRASERO_US 0x26
