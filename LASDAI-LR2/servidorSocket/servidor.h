#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include "comandos.h"

struct parametrohilo{
	struct bufferSocket _buf;
	int _fdCliente;
};

int servidor();

void *atencionCliente(void * estructura);

#endif /* _SERVIDOR_H */
