#ifndef SALIDA_DIGITAL_H
#define SALIDA_DIGITAL_H
#include "gpio.h"

/**
 * @brief Estructura que define el objeto Salida Digital
 * 
 */
typedef struct SalidaDigital{
  int estado;
  const char* nombre;
  HPin pin;
}SalidaDigital;

/**
 * @brief Inicializa la Salida Digital en configuracion PUSH-PULL
 * 
 * @param self puntero a struct SalidaDigital
 * @param nombre es el nombre del pin
 * @param pin pin que se configura como salida
 */
void SalidaDigital_init(SalidaDigital *self,const char *nombre,HPin pin);

/**
 * @brief Pone en alto la salida
 * 
 * @param self puntero a struct SalidaDIgital
 */
void SalidaDigital_enciende(SalidaDigital *self);

/**
 * @brief Pone en bajo la salida
 * 
 * @param self puntero a struct SalidaDIgital
 */
void SalidaDigital_apaga(SalidaDigital *self);

#endif
