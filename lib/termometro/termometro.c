#include "termometro.h"
#include <stdio.h>

//interfaz abstracta termometro
extern inline int Termometro_obtTemperatura(Termometro *self);
//fin interfaz abstracta

//implementacion concreta del termometro simulado 

static int obtTemperatura(Termometro *self);

static const Termometro_VT TermometroSim_vt = {
    .obtTemperatura = &obtTemperatura
};

void TermometroSimulado_init(TermometroSim *self, int temperaturaInicial)
{
    self-> termometro.vptr_ = &TermometroSim_vt;
    TermometroSimulado_ponTemperatura(self,temperaturaInicial);
}

static int obtTemperatura(Termometro *termometro)
{
    TermometroSim *const self = (TermometroSim*) termometro;
    const int temperatura = self->temperatura;
    //printf("Consulta temperatura actual: %i\n",temperatura);
    return temperatura;
}

void TermometroSimulado_ponTemperatura(TermometroSim *self, int temperatura){
    self->temperatura = temperatura;
    //printf("Termometro mide %i\n", temperatura);
}



