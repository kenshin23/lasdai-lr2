#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include "comandos.h"

struct parametrohilo{
	struct mensaje _buf;
	int _fdCliente;
};

int servidor();

void *atencionCliente(void * parametro);

#endif /* _SERVIDOR_H */
