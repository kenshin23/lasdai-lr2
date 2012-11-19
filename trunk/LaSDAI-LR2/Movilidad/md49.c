///**
// @file md25.c
// @brief Decsarrollo de las las funciones para el manejo de la placa controladora MD25.
// @date Agosors, 2011.
// @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com.
//
// Algunos datos: La controladora MD25 funciona bajo dos estandares de comunicacion Serial e I2C.
//		Permite el control de dos motores, y esta diseñada especialmente para el control de moteres EMG30.
//		Las funciones desarrolladas a continuacion representas el control del la placa MD25 en lenguaje C.
//		con comunicacion I2C usando un circuito interfaz USB-I2C S310425 que utiliza el chip USB FTDI FT232R.
//		Los controladores de este chip pueden descargarce de http://www.ftdichip.com/Products/ICs/FT232R.htm.
//		pero ya vienen incluidos en el kernel de linux a partir de la version 2.6.
//*/
//
//#include <stdio.h>
//#include <string.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <errno.h>
//#include <termios.h>
//#include "md25.h"
//
//#define DEBUG
//
///***********Funiones de comnicacion serial**************/
//
//int abrirPuerto(int *fd){
//   int _fd;
//   struct termios options;
//   _fd = open(PUERTODISPOSITIVO, O_RDWR | O_NOCTTY);
//   if (_fd >= 0){
//   	fcntl(_fd, F_SETFL, 0);
//	tcgetattr(_fd, &options);
//	cfsetispeed(&options, B19200);
//	options.c_cflag |= (CLOCAL | CREAD);
//	options.c_cflag &= ~PARENB;
//	options.c_cflag &= ~CSTOPB;
//	options.c_cflag &= ~CSIZE;
//	options.c_cflag |= CS8;
//	tcflush(_fd, TCIFLUSH);
//	tcsetattr(_fd, TCSANOW, &options);
//	fcntl(_fd, F_SETFL, FNDELAY);
//	*fd = _fd;
//	return (0);
//   }else{
//	#ifdef DEBUG
//		perror("abrirPuerto: No se puede abrir el puerto de comunicacion con el dispocitivo\n");
//	#endif
//	return (-1);
//   }
//}
//
///*******************************************************/
//
//int cerrarPuerto(int fd){
//	int respuesta;
//	respuesta = close(fd);
//	if(respuesta < 0){
//		#ifdef DEBUG
//			perror("cerrarPuerto: No se puede cerrar el puerto de comunicacion con el dispocitivo\n");
//		#endif
//		return (-1);
//	}else{
//		return (0);
//	}
//}
//
///*******************************************************/
//
//int escribirDatos(int fd, int nBytes, unsigned char *sbuf){
//	int bytes;
//	bytes = write(fd, sbuf, nBytes);
//	if(bytes < 0){
//		#ifdef DEBUG
//			perror("escribirDatos: Error no se pudieron escribir los datos\n");
//		#endif
//		return (-1);
//	}else{
//		if(bytes != nBytes){
//			#ifdef DEBUG
//				printf("escribirDatos: Error solo se logor escribir %u bytes de %u bytes \n", bytes , nBytes);
//			#endif
//			return (-2);
//		}
//		return (0);
//	}
//}
//
///*******************************************************/
//
//int leerDatos(int fd, int nBytes, unsigned char *sbuf){
//	int bytes;
//	bytes = read(fd, sbuf, nBytes);
//	if(bytes < 0){
//		#ifdef DEBUG
//			perror("leerDatos: Error no se logro leer los datos\n");
//		#endif
//		return (-1);
//	}if(bytes != nBytes){
//		#ifdef DEBUG
//			printf("leerDatos: Error solo se logro leer %u bytes de %u bytes \n", bytes, nBytes);
//		#endif
//		return (-2);
//	}
//	return (0);
//}
//
///******Funiones de manipulacion del controlador MD25******/
//
//int asignarVelocidad1(int fd, double velocidad){
//	static unsigned char sbuf[5];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_W;
//	sbuf[2] = REGISTRO_0;
//	sbuf[3] = 1;
//	sbuf[4] = velocidad;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 5, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarVelocidad1: Error al intentar escribir los datos de velocidad 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarVelocidad1: Error la escritura de la velocidad 1 no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerVelocidad1(int fd, double *velocidad){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_0;
//	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerVelocidad1: Error al enviar la solicitud de lectura para valor del registro de velocidad 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerVelocidad1: Error no se pudieron leer los datos de el registro de velocidad 1\n");
//			#endif
//			return (-2);
//		}else{
//			*velocidad = sbuf[0];
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int asignarVelocidad2(int fd, double velocidad){
//	static unsigned char sbuf[5];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_W;
//	sbuf[2] = REGISTRO_1;
//	sbuf[3] = 1;
//	sbuf[4] = velocidad;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 5, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarVelocidad2: Error al intentar escribir los datos de velocidad 2\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarVelocidad2: Error la escritura de la velocidad 2 no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerVelocidad2(int fd, double *velocidad){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_1;
//	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerVelocidad2: Error al enviar la solicitud de lectura para valor del registro de velocidad 2\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerVelocidad2: Error no se pudieron leer los datos de el registro de velocidad 2\n");
//			#endif
//			return (-2);
//		}else{
//			*velocidad = sbuf[0];
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerCodificadorMotor1(int fd, int *posicion){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_2;
//	sbuf[3] = 4;
//	unsigned long _posicion;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerCodificadorMotor1: Error al enviar la solicitud de lectura del valor codificador 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,4, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerCodificadorMotor1: Error no se pudieron leer los datos de los registro del codificador 1\n");
//			#endif
//			return (-2);
//		}else{
//			_posicion = sbuf[0];
//			_posicion = (_posicion<<8)+sbuf[1];
//			_posicion = (_posicion<<8)+sbuf[2];
//			_posicion = (_posicion<<8)+sbuf[3];
//			*posicion = (int)_posicion;
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerCodificadorMotor2(int fd, int *posicion){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_6;
//	sbuf[3] = 4;
//	unsigned long _posicion;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerCodificadorMotor1: Error al enviar la solicitud de lectura del valor codificador 2\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,4, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerCodificadorMotor1: Error no se pudieron leer los datos de los registro del codificador 2\n");
//			#endif
//			return (-2);
//		}else{
//			_posicion = sbuf[0];
//			_posicion = (_posicion<<8)+sbuf[1];
//			_posicion = (_posicion<<8)+sbuf[2];
//			_posicion = (_posicion<<8)+sbuf[3];
//			*posicion = (int)_posicion;
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerVolajeBateria(int fd, double *voltaje){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//   	sbuf[1] = MD25_R;
//   	sbuf[2] = REGISTRO_10;
//   	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerVolajeBateria: Error al enviar la solicitud de lectura del valor del voltaje\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerVolajeBateria: Error no se pudieron leer los datos de los registro del voltaje\n");
//			#endif
//			return (-2);
//		}else{
//			*voltaje = sbuf[0]/10;
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerCorrienteMotor1(int fd, double *corriente){
//	static unsigned char sbuf[4];
//	double CurrentMotor1;
//	sbuf[0] = I2C_CMD;
//   	sbuf[1] = MD25_R;
//   	sbuf[2] = REGISTRO_11;
//   	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerCorrienteMotor1: Error al enviar la solicitud de lectura del valor de la corriente del motor 1\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerCorrienteMotor1: Error no se pudieron leer los datos de los registro de corriente del motor 1\n");
//			#endif
//			return (-2);
//		}else{
//			*corriente = sbuf[0]/10;
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerCorrienteMotor2(int fd, double *corriente){
//	static unsigned char sbuf[4];
//	double CurrentMotor1;
//	sbuf[0] = I2C_CMD;
//   	sbuf[1] = MD25_R;
//   	sbuf[2] = REGISTRO_12;
//   	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerCorrienteMotor2: Error al enviar la solicitud de lectura del valor de la corriente del motor 2\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerCorrienteMotor2: Error no se pudieron leer los datos de los registro de corriente del motor 2\n");
//			#endif
//			return (-2);
//		}else{
//			*corriente = sbuf[0]/10;
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerNumeroVercion(int fd, double *version){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//   	sbuf[1] = MD25_R;
//   	sbuf[2] = REGISTRO_13;
//   	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerNumeroVercion: Error al enviar la solicitud de lectura de la version del software\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerNumeroVercion: Error no se pudo leer el registro que contiene la version del software\n");
//			#endif
//			return (-2);
//		}else{
//			*version = sbuf[0];
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int asignarModoAceleracion(int fd, int modoAceleracion){
//	static unsigned char sbuf[5];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_W;
//	sbuf[2] = REGISTRO_14;
//	sbuf[3] = 1;
//	sbuf[4] = modoAceleracion;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 5, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarModoAceleracion: Error al intentar escribir los datos del registro modo aceleracion\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarModoAceleracion: Error la escritura del registro modo aceleracion no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerModoAceleracion(int fd, int *modoAceleracion){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_14;
//	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerModoAceleracion: Error al enviar la solicitud de lectura del modo de aceleracion\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerModoAceleracion: Error no se pudo leer el registro que contiene el modo de aceleracion\n");
//			#endif
//			return (-2);
//		}else{
//			*modoAceleracion = sbuf[0];
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int asignarModoVelocidad(int fd, int modoVelocidad){
//	static unsigned char sbuf[5];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_W;
//	sbuf[2] = REGISTRO_15;
//	sbuf[3] = 1;
//	sbuf[4] = modoVelocidad;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 5, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("asignarModoVelocidad: Error al intentar escribir los datos del registro modo velocidad\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("asignarModoAceleracion: Error la escritura del registro modo velocidad no fue correcta\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int obtenerModoVelocidad(int fd, int *modoVelocidad){
//	static unsigned char sbuf[4];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_R;
//	sbuf[2] = REGISTRO_15;
//	sbuf[3] = 1;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 4, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("obtenerModoVelocidad: Error al enviar la solicitud de lectura del modo de velocidad\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("obtenerModoVelocidad: Error no se pudo leer el registro que contiene el modo de velocidad\n");
//			#endif
//			return (-2);
//		}else{
//			*modoVelocidad = sbuf[0];
//			return (0);
//		}
//	}
//}
//
///**************************************************************************************************/
//
//int enviarComando(int fd, unsigned char comando){
//	static unsigned char sbuf[5];
//	sbuf[0] = I2C_CMD;
//	sbuf[1] = MD25_W;
//	sbuf[2] = REGISTRO_16;
//	sbuf[3] = 1;
//	sbuf[4] = comando;
//	int escribir, leer;
//	escribir = escribirDatos(fd, 5, sbuf);
//	if(escribir !=  0){
//		#ifdef DEBUG
//			perror("enviarComando: Error al intentar enviar un comando\n");
//		#endif
//		return (-1);
//	}else{
//		usleep(RETRASO);
//		leer = leerDatos(fd,1, sbuf);
//		if(leer != 0){
//			#ifdef DEBUG
//				perror("enviarComando: Error el comando no fue enviado con exito\n");
//			#endif
//			return (-2);
//		}else{
//			return (0);
//		}
//	}
//}

