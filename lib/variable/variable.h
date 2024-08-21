#ifndef VARIABLE_H
#define VARIABLE_H
#include <stdio.h>

typedef struct VariableInt{
    const char* nombre;
    int valor;
}VariableInt;

/**
 * @brief Pone un valor entero
 * 
 * @param self puntero a struct VariableInt
 * @param valor valor entero que se quiere guardar
 */
static inline void VariableInt_ponValor(VariableInt *self, int valor){
    self->valor = valor;
}

/**
 * @brief Obtiene el valor guardado en un struct VariableInt
 * 
 * @param self puntero a struct VariableInt
 * @return int valor entero guardado en VariableInt
 */
static inline int VariableInt_obtValor(VariableInt *self){
    return self->valor;
}

/**
 * @brief Inicializa un valor entero a través de un struct VariableInt
 * 
 * @param self puntero a struct VariableInt
 * @param valorInicial valor entero inicial a guardar en VariableInt
 * @param nombre nombre de la variable
 */
static inline void VariableInt_init(VariableInt *self, int valorInicial, const char *nombre)
{
    self->nombre = nombre;
    VariableInt_ponValor(self,valorInicial);
}

#endif 
