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
 * @brief Inicializa la entrada digital
 * 
 * @param self puntero a struct EntradaDigital
 * @param nombre nombre asignado al pin de entrada
 * @param pin pin de entrada
 * @param nivelNormal Configuracion de la entrada:True = Pull-Up, False = Pull-Down 
 */
void EntradaDigital_init(EntradaDigital *self,const char *nombre,HPin pin, bool nivelNormal); 

/**
 * @brief Lee el valor de la entrada digital
 * 
 * @param self puntero a struct EntradaDigital
 * @return true si la entrada esta en alto
 * @return false si la entrada esta en bajo
 */
bool EntradaDigital_lee(EntradaDigital *self);

#endif

