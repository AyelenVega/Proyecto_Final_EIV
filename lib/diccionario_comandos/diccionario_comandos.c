#include "diccionario_comandos.h"
#include <string.h>

void DiccionarioComandos_init(DiccionarioComandos* self, int num_comandos, const EntradaDiccionarioComandos* comandos){
    self->num_comandos = num_comandos;
    self->comandos = comandos;
}

Comando* DiccionarioComandos_obtComando(DiccionarioComandos* self, const char* nombre){
    Comando *comando = NULL;

    for(int i=0; i < self->num_comandos; i++){
        if(!strcmp(self->comandos[i].nombre, nombre)){
            comando = self->comandos[i].comando;
            break;
        }
    }

    return comando;
}
