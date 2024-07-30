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

void ControlTemperatura_init(ControlTemperatura *self,
                             Termometro *termometro,
                             VariableInt *temperaturaDeseada,
                             SalidaDigital *calefactor);

void ControlTemperatura_ejecuta(ControlTemperatura *self);

#endif

