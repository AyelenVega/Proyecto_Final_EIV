#ifndef TERMOMETRO_H
#define TERMOMETRO_H
#include "adc.h"

typedef struct Termometro Termometro;

//tabla de  funciones virtuales
typedef struct Termometro_VT{
    int (*const obtTemperatura)(Termometro *self);
    
}Termometro_VT;

 //interfaz abstracta
struct Termometro{
    const Termometro_VT *vptr_; //virtual pointer
};

inline int Termometro_obtTemperatura(Termometro *self){
     return self->vptr_->obtTemperatura(self);
 }
 
//fin interfaz abstracta

//implementacion concreta - termometro simulado
 
typedef struct TermometroSim{
    Termometro termometro; //debe ser el primer miembro
    int temperatura;
}TermometroSim;


void TermometroSimulado_init(TermometroSim *self, int temperaturaInicial);
void TermometroSimulado_ponTemperatura(TermometroSim *self, int temperatura);

Termometro * TermometroADC_init(CanalADC canal);



#endif
