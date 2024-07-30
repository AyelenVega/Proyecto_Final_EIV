#ifndef SALIDA_DIGITAL_H
#define SALIDA_DIGITAL_H
#include "gpio.h"

typedef struct SalidaDigital{
  int estado;
  const char* nombre;
  HPin pin;
}SalidaDigital;

void SalidaDigital_init(SalidaDigital *self,const char *nombre,HPin pin);
void SalidaDigital_enciende(SalidaDigital *self);
void SalidaDigital_apaga(SalidaDigital *self);

#endif
