#include "salida_digital.h"
#include "gpio.h"
#include <stdio.h>

void SalidaDigital_init(SalidaDigital *self,const char *nombre,HPin pin){
  self->estado = 0;  //Se inicializa en 0
  self->nombre = nombre;
  self->pin = pin;
  Pin_configuraSalida(pin,PUSH_PULL,V_BAJA);
}


void SalidaDigital_enciende(SalidaDigital *self){
  if(self->estado == 0){
    Pin_ponAlto(self->pin);
    self->estado = 1;
  }
}

void SalidaDigital_apaga(SalidaDigital *self){
  if(self->estado == 1){
    Pin_ponBajo(self->pin);
    self->estado = 0;
  }
}

