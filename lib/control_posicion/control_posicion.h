#ifndef CONTROL_POSICION_H
#define CONTROL_POSICION_H
#include "motor.h"
#include "entrada_digital.h"
#include "variable_posicion.h"

typedef enum {
  ControlPosicion_Estado_PARADO,
  ControlPosicion_Estado_INGRESO,
  ControlPosicion_Estado_SALIDA
}ControlPosicion_Estado; //estado maquina de estado != estado motor

typedef struct ControlPosicion{
  ControlPosicion_Estado estado;
  VariablePos *posDeseada;
  EntradaDigital *dentro;
  EntradaDigital *fuera;
  Motor *motor;
}ControlPosicion;

/**
 * @brief Inicializa control posicion
 * 
 * @param self puntero a struct ControlPosicion
 * @param posDeseada puntero a struct VariablePos 
 * @param dentro puntero a entrada digital fin de carrera dentro
 * @param fuera puntero a entrada digital fin de carrera fuera 
 * @param motor puntero a struct Motor
 */
void ControlPosicion_init(ControlPosicion *self, 
                                VariablePos *posDeseada,
                                EntradaDigital *dentro,
                                EntradaDigital *fuera,
                                Motor *motor);

/**
 * @brief Ejecuta el control de la posicion de la bandeja 
 * 
 * @param self puntero a struct ControlPosicion
 */
void ControlPosicion_ejecuta(ControlPosicion *self);


#endif
