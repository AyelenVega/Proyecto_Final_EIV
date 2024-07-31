#include "entrada_digital.h"
#include "gpio.h"
#include <stdio.h>

void EntradaDigital_init(EntradaDigital *self,const char *nombre,HPin pin, bool nivelNormal){
    self->nombre = nombre;
    self->pin = pin;
    Pin_configuraEntrada(pin,nivelNormal ? PULL_UP:PULL_DOWN);  
    self->nivelNormal = nivelNormal;
}

bool EntradaDigital_lee(EntradaDigital *self){
    const bool valorEntrada = Pin_lee(self->pin) ^ self->nivelNormal;
    return valorEntrada;
}
