#ifndef CONTROL_TEMPERATURA_H
#define CONTROL_TEMPERATURA_H
#include "termometro.h"
#include "salida_digital.h"
#include "variable.h"

typedef enum {
    CTEstado_APAGADO,
    CTEstado_ENCENDIDO,
    CTEstado_INACTIVO
}CTEstado;

typedef struct ControlTemperatura{
    CTEstado estado;
    Termometro *termometro;
    VariableInt *temperaturaDeseada;
    SalidaDigital *calefactor;
}ControlTemperatura;

/**
 * @brief Inicializa el control de temperatura
 * 
 * @param self puntero a struct ControlTemperatura
 * @param termometro puntero a struct Termometro
 * @param temperaturaDeseada puntero a VariableInt para la temperatura deseada 
 * @param calefactor puntero a SalidaDigital para el calefactor
 */
void ControlTemperatura_init(ControlTemperatura *self,
                             Termometro *termometro,
                             VariableInt *temperaturaDeseada,
                             SalidaDigital *calefactor);

/**
 * @brief Ejecuta el control del calefactor
 * 
 * @param self puntero a struct ControlTemperatura
 */
void ControlTemperatura_ejecuta(ControlTemperatura *self);

#endif

