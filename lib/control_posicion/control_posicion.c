#include "control_posicion.h"

static CPPosicion ControlPosicion_calculaPosicion(ControlPosicion *self)
{
    const int finCarreraDentro = EntradaDigital_lee(self->dentro);
    const int finCarreraFuera  = EntradaDigital_lee(self->fuera);
    return finCarreraDentro | (finCarreraFuera << 1);
}

void ControlPosicion_init(ControlPosicion *self, 
                                VariablePos *posDeseada,
                                EntradaDigital *dentro,
                                EntradaDigital *fuera,
                                Motor *motor)
{
  self->posDeseada = posDeseada;
  self->dentro = dentro;
  self->fuera = fuera;
  self->motor = motor;
  self->estado = ControlPosicion_Estado_PARADO;
}

void ControlPosicion_ejecuta(ControlPosicion *self)
{
  const CPPosicion posDeseada = VariablePos_obtPos(self->posDeseada);
  const CPPosicion posActual = ControlPosicion_calculaPosicion(self);
  switch(self->estado){
  case ControlPosicion_Estado_PARADO:
  if (posActual == CPPosicion_INVALIDA)
  {
    self->estado = ControlPosicion_Estado_PARADO;
     Motor_apaga(self->motor);  
  } else if (posDeseada != posActual){
      if (posDeseada == CPPosicion_DENTRO){
        self->estado = ControlPosicion_Estado_INGRESO;
        Motor_ingreso(self->motor);
      }else{
        self->estado = ControlPosicion_Estado_SALIDA;
        Motor_salida(self->motor);
      }
    }
  break;
  case ControlPosicion_Estado_INGRESO:
    if (posActual== CPPosicion_INVALIDA)
      {
        self->estado = ControlPosicion_Estado_PARADO;
        Motor_apaga(self->motor);  
      } else if (posActual == CPPosicion_DENTRO){
          self->estado = ControlPosicion_Estado_PARADO;
          Motor_apaga(self->motor);
        }
  break;
  case ControlPosicion_Estado_SALIDA:
    if (posActual== CPPosicion_INVALIDA)
  {
    self->estado = ControlPosicion_Estado_PARADO;
    Motor_apaga(self->motor);  
  } else if (posActual == CPPosicion_FUERA){
      self->estado = ControlPosicion_Estado_PARADO;
      Motor_apaga(self->motor);
    }
  break;
  default:
    // Esto sería un error...
  break;
  }
}