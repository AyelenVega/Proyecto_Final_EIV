#ifndef ENTRADA_DIGITAL_H
#define ENTRADA_DIGITAL_H
#include <stdbool.h>
#include "gpio.h"

typedef struct EntradaDigital{
  bool nivelNormal;
  const char* nombre;
  HPin pin;
}EntradaDigital;

/**
 * @brief 
 * 
 * @param self 
 * @param nombre 
 * @param pin 
 * @param nivelNormal True = Pull-Up, False = Pull-Down 
 */
void EntradaDigital_init(EntradaDigital *self,const char *nombre,HPin pin, bool nivelNormal); 
bool EntradaDigital_lee(EntradaDigital *self);
void EntradaDigital_simulaValor(EntradaDigital *self, bool valor);
#endif
