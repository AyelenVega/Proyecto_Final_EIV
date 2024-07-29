#ifndef VARIABLE_H
#define VARIABLE_H
#include <stdio.h>

typedef struct VariableInt{
    const char* nombre;
    int valor;
}VariableInt;

static inline void VariableInt_ponValor(VariableInt *self, int valor){
    self->valor = valor;
    //printf("Establece %s : %i\n",self->nombre,valor);
}

static inline int VariableInt_obtValor(VariableInt *self){
    /*printf("Consulta %s : %i\n",self->nombre,self->valor);
    */
    return self->valor;
}

static inline void VariableInt_init(VariableInt *self, int valorInicial, const char *nombre)
{
    self->nombre = nombre;
    VariableInt_ponValor(self,valorInicial);
}

#endif 