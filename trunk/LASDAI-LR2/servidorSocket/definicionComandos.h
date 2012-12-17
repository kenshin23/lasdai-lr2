

#define ASIGNAR_VELOCIDAD 0X11 /** Argumentos double vl y double w **/ /** Retrun int_8bit **/

#define MOVER_LINEA_RECTA 0x12 /** Argumentos double d **/ /** Retrun int_8bit **/

#define GIRO_RELATIVO 0x13 /** Argumentos double theta **/ /** Retrun  int_8bit **/

#define GOTO_XY 0x14	/** Argumentos Struc datosCinematica (double x, double y, double theta) **/ /** Retrun int_8bit **/

#define DIAGNOSTICO_OPERATIVIDAD 0x15 /** Argumentos void **/ /** Retrun int_8bit **/

#define ASIGNAR_DATOS_CINEMATICA 0x15 /** Argumentos Struc datosCinematica (double x, double y, double theta) **/ /** Retrun  void **/

#define OBTENER_DATOS_CINEMATICA 0x17 /** Argumentos void **/ /** Retrun  Struc datosCinematica (double x, double y, double theta) **/

#define OBTENER_MEDIDA_SENSOR_US 0X21

#define OBTENER_MEDIDA_SENSOR_IR 0X22

#define OBTENER_MEDIDA_SENSOR_US_TRASERO 0X23

#define OBTENER_BARRIDO_FRONTAL_US 0x24

#define OBTENER_BARRIDO_FRONTAL_IR 0x25

#define OBTENER_BARRIDO_TRASERO_US 0x26
