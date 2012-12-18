#ifndef _COMANDOS_H
#define _COMANDOS_H

struct bufferSocket{
	unsigned char _comando;
	int _len;
	unsigned char *_argumentos;
};

int incializarRobot();

int comandos(int fdCliente, struct bufferSocket buffer);

int destruirRobot();

short int deSerializeShort(unsigned char *buf);

void serializeShort(unsigned char *buf, short int value);

double deSerializeDouble(unsigned char *buf);

void serializeDouble(unsigned char *buf, double value);



#endif
