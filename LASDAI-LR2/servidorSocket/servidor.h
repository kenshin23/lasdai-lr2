#ifndef _SERVIDOR_H
#define _SERVIDOR_H

#include "comandos.h"

#define SERVIDOR_DEBUG

int servidor();

void *atencionCliente(void * parametro);

#endif /* _SERVIDOR_H */
