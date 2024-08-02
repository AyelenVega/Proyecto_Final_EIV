#ifndef DEFINICIONES_COMANDOS_H
#define DEFINICIONES_COMANDOS_H
#include "variable.h"
#include "variable_posicion.h"
#include "termometro.h"
#include "entrada_digital.h"
#include "comando.h"

typedef struct ComandoStemp{
    Comando comando;
    VariableInt *tempDeseada;
}ComandoStemp;

typedef struct ComandoSpos{
    Comando comando;
    VariablePos *posDeseada;
}ComandoSpos;

typedef struct ComandoPos{
    Comando comando;
    EntradaDigital *fin_carrera_dentro;
    EntradaDigital *fin_carrera_fuera;
}ComandoPos;

typedef struct ComandoTemp{
    Comando comando;
    Termometro *termometro;
}ComandoTemp;

void ComandoStemp_init(ComandoStemp *self, VariableInt *tempDeseada);
void ComandoSpos_init(ComandoSpos *self, VariablePos *posDeseada);
void ComandoPos_init(ComandoPos *self, EntradaDigital *fin_carrera_dentro, EntradaDigital *fin_carrera_fuera);
void ComandoTemp_init(ComandoTemp *self, Termometro *termometro);

#endif