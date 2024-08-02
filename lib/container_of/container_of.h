#ifndef CONTAINER_OF
#define CONTAINER_OF
#include <stddef.h>

#define container_of(puntero,tipoContenedor,miembro) ((tipoContenedor*)((char*)(1?(puntero):&((tipoContenedor*)0)->miembro) - offsetof(tipoContenedor,miembro)))

#endif