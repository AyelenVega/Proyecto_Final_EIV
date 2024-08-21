#include "termometro.h"
#include "adc.h"


static int obtTemperatura (Termometro *self);

/**
 * @brief Implementacion concreta de la tabla virtual de funciones para TermometroADC
 * 
 */
static const Termometro_VT TermometroADC_vt = {
    .obtTemperatura = &obtTemperatura
};

static Termometro termometroADC;

/**
 * @brief Inicializa el ADC y Termometro
 * 
 * @param canal canal del ADC
 * @return Termometro* Puntero a TermometroADC
 */
Termometro * TermometroADC_init(CanalADC canal){
    adc_init (canal);
    termometroADC.vptr_ = &TermometroADC_vt;
    return &termometroADC;
}

/**
 * @brief Obtiene temperatura en [°C]
 * 
 * @param self Puntero a struct Termometro (ADC) 
 * @return int Temperatura medida [°C]
 */
static int obtTemperatura (Termometro *self){
    (void) self;
    enum {
       V_REF = 3300, // [mV]
       NUM_BITS = 12,
       T0 = 0, // [°C]
       TENSION_POR_GRADO = 10 // [mV]
    };
   const int valorLeido = adc_lee();
   const int tension = (valorLeido * V_REF) / (1 << NUM_BITS);
   const int temperatura = (tension / TENSION_POR_GRADO) + T0;
  
   return temperatura;
}
