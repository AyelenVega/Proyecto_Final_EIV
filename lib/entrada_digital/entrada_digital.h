#ifndef ENTRADA_DIGITAL_H
#define ENTRADA_DIGITAL_H
#include <stdbool.h>
#include "gpio.h"

typedef struct EntradaDigital{
  bool estado;
  const char* nombre;
  HPin pin;
}EntradaDigital;

void EntradaDigital_init(EntradaDigital *self,const char *nombre,HPin pin);
bool EntradaDigital_lee(EntradaDigital *self);
void EntradaDigital_simulaValor(EntradaDigital *self, bool valor);
#endif