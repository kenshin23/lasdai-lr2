/**
 @file   definicion.h
 @brief  Definición de las variables y comando utilizadas por las rutinas de manipulacion de la tarjeta controladora de motores MD49.
 @date   Octubre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
*/

/** DEFINICIONES MD49*/

/** Activación del modo depuración para las rutinas de MD49 **/
#define DEBUG

/** Puerto de Trabajo del la comunicación serial con la MD49 tty **/
#define ttyMD49 "ttyUSB0"

/** Velocidad de trabajo de la comunicación Serial con la MD49 **/
#define baudiosMD49 38400

/** Tiempo de retraso para esperar respuesta de la MD49 después de escribir **/
#define retraso 7800

/** Se enviá en el bufer antes de cada comando. */
#define  byteDeSincronizacion 0x00

/** COMANDOS */

/** Comando para obtener la velocidad actual del motor 1. */
#define comandoObtenerVelocidad1 0x21

/** Comando para obtener la velocidad actual del motor 2. */
#define comandoObtenerVelocidad2 0x22

/** Comando para obtener el contador del codificador del motor 1. */
#define comandoObtenerCodificadorMotor1 0x23

/** Comando para obtener el contador del codificador del motor 2. */
#define comandoObtenerCodificadorMotor2 0x24

/** Comando para obtener el contador de los codificadores de ambos motores. */
#define comandoObtenerCodificadorMotores 0x25

/** Comando para obtener el Voltaje de la bateria que alimenta la MD49. */
#define comandoObtenerVoltajeBateria 0x26

/** Comando para obtener la corriente consumida por el motor 1. */
#define comandoObtenerCorrienteMotor1 0x27

/** Comando para obtener la corriente consumida por el motor 2. */
#define comandoObtenerCorrienteMotor2 0x28

/** Comando para obtener la version del software de la MD49. */
#define comandoObtenerVersionSoftware 0x29

/** Comando para obtener el nivel de aceleración actual. */
#define comandoObtenerAceleracion 0x2A

/** Comando para obtener el modo de velocidad actual. */
#define comandoObtenerModoVelocidad 0x2B

/** Comando para obtener el voltaje de la batería y la la corriente consumida por cada motor. */
#define comandoObtenerDatosEnergia 0x2C

/** Comando para obtener el error indicado por el manejador de errores de la MD49. */
#define comandoObtenerError 0x2D

/** Comando para asignar la velocidad 1 la funcionalidad de este comando depende del modo en que se este trabajando*/
#define comandoAsignarVelocidad1 0x31

/** Comando para asignar la velocidad 2 la funcionalidad de este comando depende del modo en que se este trabajando*/
#define comandoAsignarVelocidad2 0x32

/** Comando para asignar la aceleración deseada */
#define comandoAsignarAceleracion 0x33

/** Comando para seleccionar el mode de trabajo deseado */
#define comandoSeleccionarModoVelocidad 0x34

/** Comando para reiniciar el contador de los codificadores de los motores */
#define comandoReinicioContadorCodificador 0x35

/** Comando para desactivar la variación de la potencia de salida a través de la retroalimentación de los codificadores */
#define comandoDesactivarRetroalimentacion 0x36

/** Comando para activar la variación de la potencia de salida a través de la retroalimentación de los codificadores */
#define comandoActivarRetroalimentacion 0x37

/** Comando para desactivar el tiempo de seguridad que detiene la funcionalidad de la MD49 después de 2 seg sin comunicación*/
#define comandoDesactivarTiempoSeguridad 0x38

/** Comando para activar el tiempo de seguridad que detiene la funcionalidad de la MD49 después de 2 seg sin comunicación*/
#define comandoActivarTiempoSeguridad 0x39



