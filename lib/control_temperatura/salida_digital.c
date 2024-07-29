#include "salida_digital.h"
#include <stdio.h>

void SalidaDigital_init(SalidaDigital *self,const char *nombre)
{
  self->estado = 0;
  self->nombre = nombre;
}
void SalidaDigital_enciende(SalidaDigital *self)
{
  self->estado = 1;
  //printf("Se enciende %s\n",self->nombre);
}
void SalidaDigital_apaga(SalidaDigital *self)
{
  self->estado = 0;
  //printf("Se apaga %s\n",self->nombre);
}
