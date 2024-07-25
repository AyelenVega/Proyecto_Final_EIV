#include "control_posicion.h"

static CPPosicion ControlPosicion_calculaPosicion(ControlPosicion *self)
{
    const int finCarreraDentro = EntradaDigital_lee(self->dentro);
    const int finCarreraFuera  = EntradaDigital_lee(self->fuera);
    return finCarreraDentro | (finCarreraFuera << 1);
}

void ControlPosicion_init(ControlPosicion *self, 
                                CPPosicion (*obtPosicionDeseada)(void),
                                EntradaDigital *dentro,
                                EntradaDigital *fuera,
                                Motor *motor)
{
  self->obtPosicionDeseada = obtPosicionDeseada;
  self->dentro = dentro;
  self->fuera = fuera;
  self->motor = motor;
  self->estado = ControlPosicion_Estado_PARADO;
}

void ControlPosicion_ejecuta(ControlPosicion *self)
{
  const CPPosicion posDeseada = self->obtPosicionDeseada();
  const CPPosicion posActual = ControlPosicion_calculaPosicion(self);
  switch(self->estado){
  case ControlPosicion_Estado_PARADO:
    if (posDeseada != posActual){
      if (posDeseada == CPPosicion_DENTRO){
        self->estado = ControlPosicion_Estado_INGRESO;
        Motor_ingreso(self->motor);
      }else{
        self->estado = ControlPosicion_Estado_SALIDA;
        Motor_salida(self->motor);
      }
    }
  break;case ControlPosicion_Estado_INGRESO:
    if (posActual == CPPosicion_DENTRO){
      self->estado = ControlPosicion_Estado_PARADO;
      Motor_apaga(self->motor);
    }
  break;case ControlPosicion_Estado_SALIDA:
    if (posActual == CPPosicion_FUERA){
      self->estado = ControlPosicion_Estado_PARADO;
      Motor_apaga(self->motor);
}
  break;default:
    // Esto sería un error...
  break;
  }
}