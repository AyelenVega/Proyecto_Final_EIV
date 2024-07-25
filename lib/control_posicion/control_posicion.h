#ifndef CONTROL_POSICION_H
#define CONTROL_POSICION_H
#include "motor.h"
#include "entrada_digital.h"

typedef enum {
  ControlPosicion_Estado_PARADO,
  ControlPosicion_Estado_INGRESO,
  ControlPosicion_Estado_SALIDA
}ControlPosicion_Estado; //estado maquina de estado != estado motor

typedef enum{
  CPPosicion_EN_TRANSITO = 0b00,
  CPPosicion_DENTRO = 0b01,
  CPPosicion_FUERA = 0b10,
  CPPosicion_INVALIDA = 0b11
}CPPosicion;

typedef struct ControlPosicion{
  ControlPosicion_Estado estado;
  CPPosicion (*obtPosicionDeseada)(void);
  EntradaDigital *dentro;
  EntradaDigital *fuera;
  Motor *motor;
}ControlPosicion;

void ControlPosicion_init(ControlPosicion *self, 
                                CPPosicion (*obtPosicionDeseada)(void),
                                EntradaDigital *dentro,
                                EntradaDigital *fuera,
                                Motor *motor);

void ControlPosicion_ejecuta(ControlPosicion *self);



#endif
