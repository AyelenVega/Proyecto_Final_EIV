#include "entrada_digital.h"
#include "gpio.h"
#include <stdio.h>

void EntradaDigital_init(EntradaDigital *self,const char *nombre,HPin pin){
    self->nombre = nombre;
    self->pin = pin;
    Pin_configuraEntrada(pin,PULL_UP);  //se podria incluir un parametro para PULL UP o PULL DOWN
    self->estado = true;
}

bool EntradaDigital_lee(EntradaDigital *self){
    const bool valorEntrada = Pin_lee(self->pin);
    self->estado = Pin_lee(self->pin);
    /*printf("Consulta estado %s: %i\n",self->nombre,(int)valorEntrada);
    */
    return valorEntrada;
}

void EntradaDigital_simulaValor(EntradaDigital *self, bool valor){
    self->estado = valor;
    /*printf("Cambio estado de entrada %s a %i\n",self->nombre,(int)valor);
    */
}