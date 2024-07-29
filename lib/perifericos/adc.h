#ifndef ADC_H
#define ADC_H
#include "gpio.h"

typedef enum CanalADC{
    CanalADC_0,
    CanalADC_1,
    CanalADC_2,
    CanalADC_3,
    CanalADC_4,
    CanalADC_5,
    CanalADC_6,
    CanalADC_7,
    CanalADC_8,
    CanalADC_9,
    CanalADC_TSENS=16,
    CanalADC_VREF=17,
    CanalADC_INVALIDO
}CanalADC;

void adc_init (CanalADC canal);
int adc_lee (void);

#endif