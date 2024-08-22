#ifndef TERMOMETRO_H
#define TERMOMETRO_H
#include "adc.h"

typedef struct Termometro Termometro;

/**
 * @brief Tabla virtual de funciones (VT = Virtual Table)
 * 
 */
typedef struct Termometro_VT{
    int (*const obtTemperatura)(Termometro *self);
    
}Termometro_VT;

 //INTERFAZ ABSTRACTA:

/**
 * @brief define el objeto "Termometro"
 * 
 */
struct Termometro{
    const Termometro_VT *vptr_; //Virtual pointer
};

/**
 * @brief Obtiene temperatura
 * 
 * @param self puntero a struct Termometro
 * @return int temperatura obtenida
 */
inline int Termometro_obtTemperatura(Termometro *self){
     return self->vptr_->obtTemperatura(self);
 }
 
//FIN INTERFAZ ABSTRACTA

//IMPLEMENTACION CONCRETA - Termometro ADC
 
Termometro * TermometroADC_init(CanalADC canal);


#endif
