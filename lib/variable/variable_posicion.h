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

static const char * describePosicion(CPPosicion pos)
{
  switch (pos){
  case CPPosicion_EN_TRANSITO: return "en transito";
  case CPPosicion_DENTRO: return "dentro";
  case CPPosicion_FUERA: return "fuera";
  default: return "NO VALIDO";
  }
}

static inline void VariablePos_ponPosicion(VariablePos *self, CPPosicion posicion){
    self->posicion = posicion;
    /*printf("Establece %s : %s\n",self->nombre,describePosicion(posicion));
    */
}

static inline CPPosicion VariablePos_obtPos(VariablePos *self){
    //printf("Consulta %s : %s\n",self->nombre,describePosicion(self->posicion));
    return self->posicion;
}

static inline void VariablePos_init(VariablePos *self, CPPosicion posInicial, const char *nombre)
{
    self->nombre = nombre;
    VariablePos_ponPosicion(self,posInicial);
}

#endif