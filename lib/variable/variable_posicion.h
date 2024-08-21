#ifndef VARIABLE_POSICION_H
#define VARIABLE_POSICION_H
#include <stdio.h>

typedef enum{
  CPPosicion_EN_TRANSITO = 0b00,
  CPPosicion_DENTRO = 0b01,
  CPPosicion_FUERA = 0b10,
  CPPosicion_INVALIDA = 0b11
}CPPosicion;

typedef struct VariablePos{
    const char* nombre;
    CPPosicion posicion;
}VariablePos;

/**
 * @brief Establece la posicion de la bandeja
 * 
 * @param self puntero a struct VariablePos
 * @param posicion posicion de la bandeja
 */
static inline void VariablePos_ponPosicion(VariablePos *self, CPPosicion posicion){
    self->posicion = posicion;
}

/**
 * @brief Obtiene la posicion de la bandeja
 * 
 * @param self puntero a struct VariablePos
 * @return CPPosicion posicion de la bandeja
 */
static inline CPPosicion VariablePos_obtPos(VariablePos *self){
    return self->posicion;
}

/**
 * @brief Inicializa el struct VariablePos
 * 
 * @param self puntero a struct VariablePos
 * @param posInicial Posicion inicial de la bandeja 
 * @param nombre Nombre de la variable
 */
static inline void VariablePos_init(VariablePos *self, CPPosicion posInicial, const char *nombre)
{
    self->nombre = nombre;
    VariablePos_ponPosicion(self,posInicial);
}

#endif
