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

int obtenerMedidaSensorUS(int idSensorUS);

int obtenerMedidaSensorIR(int idSensorIR);

int obtenerMedidaSensorTraseroUS(int angulo);

int obtenerBarridoFrontalUS();

int obtenerBarridoFrontalIR();

int obtenerBarridoTraseroUS();

int terminarComunicacionSP(int fd);

#endif /* PERCEPCION_H_ */