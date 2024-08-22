#ifndef ADC_H
#define ADC_H
#include "gpio.h"

/**
 * @brief Canales del conversor AD
 * 
 */
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

/**
 * @brief Inicializa el conversor AD
 * 
 * @param canal es el canal a utilizar
 */
void adc_init (CanalADC canal);

/**
 * @brief Realiza la conversion y devuelve el valor convertido
 * 
 * @return int valor convertido
 */
int adc_lee (void);

#endif
