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
 @file md49.c
 @brief Desarrollo de los métodos para el manejo de la placa controladora MD49 definidos en md49.h.
 @date Junio, 2012.
 @author José Delgado Pérez, josedelgado@ula.ve josed43@gmail.com.
 @version 0.9
*/

#include "md49.h"

/****** Métodos de manipulación del controlador MD49 ******/

int iniciarComunicacionMD49(){
	int com;
	com = abrirPuerto(&fd,TTY_MD49,BAUDIOS_MD49);
	if(com !=  0){
			#ifdef MD49_DEBUG
				perror("iniciarComunicacionMD49: Error al iniciar la comunicación con la MD49.\n");
			#endif
			return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int obtenerVelocidad1(double *velocidad){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_VELOCIDAD_1;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerVelocidad1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerVelocidad2(double *velocidad){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_VELOCIDAD_2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerVelocidad2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerCodificadorMotor1(int *codificadorPosicion1){
	static unsigned char sbuf[4];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_CODIFICADOR_MOTOR_1;
	unsigned long _codificador;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerCodificadorMotor1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,4, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerCodificadorMotor2(int *codificadorPosicion2){
	static unsigned char sbuf[4];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_CODIFICADOR_MOTOR_2;
	unsigned long _codificador;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerCodificadorMotor2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,4, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerCodificadoresMotores(int *codificadorPosicion1, int *codificadorPosicion2){
	static unsigned char sbuf[8];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_CODIFICADOR_MOTORES;
	unsigned long _codificador1, _codificador2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerCodificadorMotores: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,8, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerVolajeBateria(double *voltajeBateria){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
   	sbuf[1] = COMANDO_OBTENER_VOLTAJE_BATERIA;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerVolajeBateria: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerCorrienteMotor1(double *corrienteMotor1){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
   	sbuf[1] = COMANDO_OBTENER_CORRIENTE_MOTOR_1;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerCorrienteMotor1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
				perror("obtenerCorrienteMotor1: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*corrienteMotor1 = sbuf[0]/10;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerCorrienteMotor2(double *corrienteMotor2){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
   	sbuf[1] = COMANDO_OBTENER_CORRIENTE_MOTOR_2;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerCorrienteMotor2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
				perror("obtenerCorrienteMotor2: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			*corrienteMotor2 = sbuf[0]/10;
			return (0);
		}
	}
}

/**************************************************************************************************/

int obtenerNumeroVersionSoftware(double *versionSoftware){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
   	sbuf[1] = COMANDO_OBTENER_VERSION_SOFTWARE;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerNumeroVersion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerModoAceleracion(int *modoAceleracion){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_MODO_ACELERACION;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerModoAceleracion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerModoVelocidad(int *modoVelocidad){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_MODO_VELOCIDAD;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerModoVelocidad: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerDatosEnergia(double *voltajeBateria, double *corrienteMotor1, double *corrienteMotor2){
	static unsigned char sbuf[3];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_DATOS_ENERGIA;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerDatosEnergia: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,3, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
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

int obtenerError(int *error){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_OBTENER_ERROR;
	int escribir, leer;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("obtenerError: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		usleep(RETRASOMD49);
		leer = leerDatos(fd,1, sbuf);
		if(leer != 0){
			#ifdef MD49_DEBUG
				perror("obtenerError: Error el comando no se ejecuto correctamente.\n");
			#endif
			return (-2);
		}else{
			if(sbuf[0] == 0){
				*error = 0; //no hay ningún error en la controladora MD49.
			}
			if(sbuf[0] & ERROR_BAJO_VOLTAJE){
				*error = -1; //error -1: se detecto bajo voltaje en la alimentación de la MD49.
			}
			if(sbuf[0] & ERROR_ALTO_VOLTAJE){
				*error = -2; //error -2: se detecto alto voltaje en la alimentación de la MD49.
			}
			if(sbuf[0] & ERROR_CORRIENTE_MOTOR_1){
				*error = -3; //error -3: se detecto alto consumo de corriente por parte del motor 1.
			}
			if(sbuf[0] & ERROR_CORRIENTE_MOTOR_2){
				*error = -4; //error -4: se detecto alto consumo de corriente por parte del motor 2.
			}
			if(sbuf[0] & ERROR_CORTO_MOTOR_1){
				*error = -5; //error -5: se detecto corto en el motor 1.
			}
			if(sbuf[0] & ERROR_CORTO_MOTOR_2){
				*error = -6; //error -6: se detecto corto en el motor 2.
			}
			return (0);
		}
	}
}

/**************************************************************************************************/

int asignarVelocidad1(double velocidad1){
	static unsigned char sbuf[3];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ASIGNAR_VELOCIDAD_1;
	sbuf[2] = velocidad1;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("asignarVelocidad1: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int asignarVelocidad2(double velocidad2){
	static unsigned char sbuf[3];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ASIGNAR_VELOCIDAD_2;
	sbuf[2] = velocidad2;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("asignarVelocidad2: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int asignarModoAceleracion(int modoAceleracion){
	static unsigned char sbuf[3];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ASIGNAR_MODO_ACELERACION;
	sbuf[2] = modoAceleracion;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("asignarModoAceleracion: Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int asignarModoVelocidad(int modoVelocidad){
	static unsigned char sbuf[3];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ASIGNAR_MODO_VELOCIAD;
	sbuf[2] = modoVelocidad;
	int escribir;
	escribir = escribirDatos(fd, 3, sbuf);
	if(escribir !=  0){
		#ifdef MD49_DEBUG
			perror("asignarModoVelocidad:Error al intenetar escribir el comando.\n");
		#endif
		return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int reinicializarCodificadores(){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_REINICIO_CONTADOR_CODIFICADOR;
	int escribir;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef MD49_DEBUG
				perror("reinicializarCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
			return (0);
	}
}

/**************************************************************************************************/

int activarRetroalimentacionCodificadores(){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ACTIVAR_RETROALIMENTACION;
	int escribir;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef MD49_DEBUG
				perror("activarRetroalimentacionCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		return (0);
	}
}

/**************************************************************************************************/

int desactivarRetroalimentacionCodificadores(){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_DESACTIVAR_RETROALIMENTACION;
	int escribir;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef MD49_DEBUG
				perror("desactivarRetroalimentacionCodificadores: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
			return (0);
	}
}

/**************************************************************************************************/

int activarTiempoSeguridad(){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_ACTIVAR_TIEMPO_SEGURIDAD;
	int escribir;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef MD49_DEBUG
				perror("activarTiempoSeguridad: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		return 0;
	}
}

/**************************************************************************************************/

int desactivarTiempoSeguridad(){
	static unsigned char sbuf[2];
	sbuf[0] = BYTE_SINCRONIZACION;
	sbuf[1] = COMANDO_DESACTIVAR_TIEMPO_SEGURIDAD;
	int escribir;
	escribir = escribirDatos(fd, 2, sbuf);
	if(escribir !=  0){
			#ifdef MD49_DEBUG
				perror("desactivarTiempoSeguridad: Error al intenetar escribir el comando.\n");
			#endif
			return (-1);
	}else{
		return 0;
	}
}

/**************************************************************************************************/

int terminarComunicacionMD49(){
	int com;
	com = cerrarPuerto(fd);
	if(com !=  0){
			#ifdef MD49_DEBUG
				perror("terminarComunicacionMD49: Error al terminar la comunicación con la MD49.\n");
			#endif
			return (-1);
	}else{
		return (0);
	}
}
