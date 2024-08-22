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

/**
 * @brief inicializa ComandoStemp  
 * 
 * @param self puntero a struct ComandoStemp
 * @param tempDeseada puntero a VariableInt para temperatura deseada
 */
void ComandoStemp_init(ComandoStemp *self, VariableInt *tempDeseada);

/**
 * @brief  inicializa ComandoSpos
 * 
 * @param self puntero a struct ComandoSPos
 * @param posDeseada puntero a VariablePos 
 */
void ComandoSpos_init(ComandoSpos *self, VariablePos *posDeseada);

/**
 * @brief inicializa Pos
 * 
 * @param self puntero a struct ComandoPos
 * @param fin_carrera_dentro puntero a entrada digital de fin carrera dentro
 * @param fin_carrera_fuera puntero a entrada digital fin de carrera fuera
 */
void ComandoPos_init(ComandoPos *self, EntradaDigital *fin_carrera_dentro, EntradaDigital *fin_carrera_fuera);

/**
 * @brief  inicializa Temp
 * 
 * 
 * @param self puntero a struct Temp
 * @param termometro puntero a termometro
 */
void ComandoTemp_init(ComandoTemp *self, Termometro *termometro);

#endif
