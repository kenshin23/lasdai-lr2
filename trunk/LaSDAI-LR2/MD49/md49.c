/**
 @file md49.c
 @brief Desarrollo de los metodos para el manejo de la placa controladora MD49 definidos en md49.h.
 @date Junio, 2012.
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#include "md49.h"
#include "definicion.h"
#include "../ComunicacionSerial/serial.h"

/****** Metodos de manipulaciónn del controlador MD49 ******/

int obtenerVelocidad1(int fd, double *velocidad){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerVelocidad1;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerVelocidad1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerVelocidad1: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*velocidad = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerVelocidad2(int fd, double *velocidad){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerVelocidad2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerVelocidad2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerVelocidad2: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*velocidad = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCodificadorMotor1(int fd, int *codificadorPosicion1){
	static unsigned char sbuf[4];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerCodificadorMotor1;
	unsigned long _codificador;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerCodificadorMotor1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,4, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerCodificadorMotor1: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			_codificador = sbuf[0];
			_codificador = (_codificador<<8)+sbuf[1];
			_codificador = (_codificador<<8)+sbuf[2];
			_codificador = (_codificador<<8)+sbuf[3];
			*codificadorPosicion1 = (int)_codificador;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCodificadorMotor2(int fd, int *codificadorPosicion2){
	static unsigned char sbuf[4];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerCodificadorMotor2;
	unsigned long _codificador;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerCodificadorMotor2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,4, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerCodificadorMotor2: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			_codificador = sbuf[0];
			_codificador = (_codificador<<8)+sbuf[1];
			_codificador = (_codificador<<8)+sbuf[2];
			_codificador = (_codificador<<8)+sbuf[3];
			*codificadorPosicion2 = (int)_codificador;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCodificadorMotores(int fd, int *codificadorPosicion1, int *codificadorPosicion2){
	static unsigned char sbuf[8];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerCodificadorMotores;
	unsigned long _codificador1, _codificador2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerCodificadorMotores: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,8, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerCodificadorMotores: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			_codificador1 = sbuf[0];
			_codificador1 = (_codificador1<<8)+sbuf[1];
			_codificador1 = (_codificador1<<8)+sbuf[2];
			_codificador1 = (_codificador1<<8)+sbuf[3];
			*codificadorPosicion1 = (int)_codificador1;
			_codificador2 = sbuf[4];
			_codificador2 = (_codificador2<<8)+sbuf[5];
			_codificador2 = (_codificador2<<8)+sbuf[6];
			_codificador2 = (_codificador2<<8)+sbuf[7];
			*codificadorPosicion2 = (int)_codificador2;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerVolajeBateria(int fd, double *voltajeBateria){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
   	sbuf[1] = comandoObtenerVoltajeBateria;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerVolajeBateria: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerVolajeBateria: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*voltajeBateria = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCorrienteMotor1(int fd, double *corrienteMotor1){
	static unsigned char sbuf[2];
	double _corrienteMotor1;
	sbuf[0] = byteDeSincronizacion;
   	sbuf[1] = comandoObtenerCorrienteMotor1;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerCorrienteMotor1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerCorrienteMotor1: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*_corrienteMotor1 = sbuf[0]/10;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCorrienteMotor2(int fd, double *corrienteMotor2){
	static unsigned char sbuf[2];
	double _corrienteMotor2;
	sbuf[0] = byteDeSincronizacion;
   	sbuf[1] = comandoObtenerCorrienteMotor2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerCorrienteMotor2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerCorrienteMotor2: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*_corrienteMotor2 = sbuf[0]/10;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerNumeroVersionSoftware(int fd, double *versionSoftware){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
   	sbuf[1] = comandoObtenerVersionSoftware;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerNumeroVersion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerNumeroVersion: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*versionSoftware = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerModoAceleracion(int fd, int *modoAceleracion){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerAceleracion;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerModoAceleracion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerModoAceleracion: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*modoAceleracion = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerModoVelocidad(int fd, int *modoVelocidad){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerModoVelocidad;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerModoVelocidad: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerModoVelocidad: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*modoVelocidad = sbuf[0];
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerDatosEnergia(int fd, int *voltajeBateria, int *corrienteMotor1, int *corrienteMotor2){
	static unsigned char sbuf[3];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerDatosEnergia;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerDatosEnergia: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,3, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerDatosEnergia: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*voltajeBateria = sbuf[0];
			*corrienteMotor1 = sbuf[1]/10;
			*corrienteMotor2 = sbuf[2]/10;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerError(int fd, int *error){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoObtenerError;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("obtenerError: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("obtenerError: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*error = sbuf[0]; //Ojo esto esta mal.
			return (0);
		}
	}
}

/**************************************************************************************************/

int asignarVelocidad1(int fd, double velocidad){
	static unsigned char sbuf[3];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoAsignarVelocidad1;
	sbuf[2] = velocidad;
	int escribir,leer;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("asignarVelocidad1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("asignarVelocidad1: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int asignarVelocidad2(int fd, double velocidad){
	static unsigned char sbuf[3];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoAsignarVelocidad2;
	sbuf[2] = velocidad;
	int escribir,leer;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("asignarVelocidad2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("asignarVelocidad2: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int asignarModoAceleracion(int fd, int modoAceleracion){
	static unsigned char sbuf[3];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoAsignarAceleracion;
	sbuf[2] = modoAceleracion;
	int escribir, leer;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("asignarModoAceleracion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("asignarModoAceleracion: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int asignarModoVelocidad(int fd, int modoVelocidad){
	static unsigned char sbuf[3];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoSeleccionarModoVelocidad;
	sbuf[2] = modoVelocidad;
	int escribir, leer;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef DEBUG
			perror("asignarModoVelocidad:Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("asignarModoAceleracion: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int reinicializarCodificadores(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoReinicioContadorCodificador;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef DEBUG
				perror("reinicializarCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("reinicializarCodificadores: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int activarRetroalimentacionCodificadores(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoActivarRetroalimentacion;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef DEBUG
				perror("activarRetroalimentacionCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("activarRetroalimentacionCodificadores: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int desactivarRetroalimentacionCodificadores(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoDesactivarRetroalimentacion;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef DEBUG
				perror("desactivarRetroalimentacionCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("desactivarRetroalimentacionCodificadores: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int activarTiempoSeguridad(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoActivarTiempoSeguridad;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef DEBUG
				perror("activarTiempoSeguridad: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("activarTiempoSeguridad: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}

/**************************************************************************************************/

int desactivarTiempoSeguridad(int fd){
	static unsigned char sbuf[2];
	sbuf[0] = byteDeSincronizacion;
	sbuf[1] = comandoDesactivarTiempoSeguridad;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef DEBUG
				perror("desactivarTiempoSeguridad: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		usleep(retraso);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef DEBUG
				perror("desactivarTiempoSeguridad: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			return (0);
		}
	}
}





























