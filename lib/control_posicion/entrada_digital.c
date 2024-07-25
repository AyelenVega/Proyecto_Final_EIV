#include "entrada_digital.h"
#include <stdio.h>

void EntradaDigital_init(EntradaDigital *self,const char *nombre){
    self->nombre = nombre;
    EntradaDigital_simulaValor(self,false);
}
bool EntradaDigital_lee(EntradaDigital *self){
    const bool valorEntrada = self->estado;
    printf("Consulta estado %s: %i\n",self->nombre,(int)valorEntrada);
    return valorEntrada;
}
void EntradaDigital_simulaValor(EntradaDigital *self, bool valor)
{
    self->estado = valor;
    printf("Cambio estado de entrada %s a %i\n",self->nombre,(int)valor);
}