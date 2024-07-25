#ifndef CONTROL_TEMPERATURA_H
#define CONTROL_TEMPERATURA_H
#include "termometro.h"
#include "salida_digital.h"

typedef enum {
    CTEstado_APAGADO,
    CTEstado_ENCENDIDO,
    CTEstado_INACTIVO
}CTEstado;

typedef struct ControlTemperatura{
    CTEstado estado;
    Termometro *termometro;
    int (*obtenerTemperaturaDeseada)(void);
    SalidaDigital *calefactor;
    void(*apagaCalefactor)(void);
}ControlTemperatura;

void ControlTemperatura_init(ControlTemperatura *self,
                             Termometro *termometro,
                             int (*obtenerTemperaturaDeseada)(void),
                             SalidaDigital *calefactor);

void ControlTemperatura_ejecuta(ControlTemperatura *self);

#endif
