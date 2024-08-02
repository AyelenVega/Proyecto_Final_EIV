#ifndef DICCIONARIO_COMANDOS_H
#define DICCIONARIO_COMANDOS_H
#include "comando.h"

typedef struct EntradaDiccionarioComandos{
    const char* nombre;
    Comando* comando;
}EntradaDiccionarioComandos;

typedef struct DiccionarioComandos{
    int num_comandos;
    const EntradaDiccionarioComandos* comandos;
}DiccionarioComandos;

void DiccionarioComandos_init(DiccionarioComandos* self, int num_comandos, const EntradaDiccionarioComandos* comandos);
Comando* DiccionarioComandos_obtComando(DiccionarioComandos* self, const char* nombre);

#endif