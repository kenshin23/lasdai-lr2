#ifndef _COMANDOS_H
#define _COMANDOS_H

struct tipoComando{
	unsigned char _comando;
	uint8_t _len;
	unsigned char *_argumentos;
};


int comandos(struct tipoComando comando);

short int deSerializeShort(uint8_t *buf);

void serializeShort(uint8_t *buf, short int value);

double deSerializeDouble(uint8_t *buf);

void serializeDouble(uint8_t *buf, double value);

#endif
