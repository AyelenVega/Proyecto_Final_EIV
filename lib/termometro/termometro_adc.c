#include "termometro.h"
#include "adc.h"


static int obtTemperatura (Termometro *self);

static const Termometro_VT TermometroADC_vt = {
    .obtTemperatura = &obtTemperatura
};

static Termometro termometroADC;

Termometro * TermometroADC_init(CanalADC canal){
    adc_init (canal);
    termometroADC.vptr_ = &TermometroADC_vt;
    return &termometroADC;
}

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