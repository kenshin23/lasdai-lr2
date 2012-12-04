/**
 @file   percepcion.h
 @brief
 @date   Diciembre, 2012
 @author José Delgado Pérez josedelgado@ula.ve josed43@gmail.com
 @version 0.9

*/

#ifndef PERCEPCION_H_
#define PERCEPCION_H_

int iniciarComunicacionSP(int *fd);

int obtenerMedidaSensorUS(int fd, int idSensorUS, int *distanciaUS);

int obtenerMedidaSensorIR(int fd, int idSensorIR, int *distanciaIR);

int obtenerMedidaSensorTraseroUS(int angulo);

int obtenerBarridoFrontalUS();

int obtenerBarridoFrontalIR();

int obtenerBarridoTraseroUS();

int terminarComunicacionSP(int fd);

#endif /* PERCEPCION_H_ */
