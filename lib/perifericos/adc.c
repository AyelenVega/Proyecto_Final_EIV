#include "adc.h"
#include "gpio.h"
#include "stm32f10x.h"

static void ajustaDivADC(void){
    SystemCoreClockUpdate();
    const uint32_t divAPB2 = (RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;
    const uint32_t relojAPB2 = SystemCoreClock >> ((divAPB2 & 0b100) ? (divAPB2&0b11) + 1 : 0);
    const uint32_t divisorRequerido = ((relojAPB2 + (14000000UL-1)) / 14000000UL);
    const uint32_t configDivisor = (divisorRequerido <= 2) ? 0b00:
                                   (divisorRequerido <= 4) ? 0b01:
                                   (divisorRequerido <= 6) ? 0b10:
                                                             0b11;}
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_ADCPRE) | (configDivisor << RCC_CFGR_ADCPRE_Pos);
}

static void calibraAdc(void){
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while(ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while(ADC1->CR2 & ADC_CR2_CAL);
}

void adc_init (CanalADC canal){
    static const HPin pinDeCanal[]={
        [CanalADC_0] = PA0,
        [CanalADC_1] = PA1,
        [CanalADC_2] = PA2,
        [CanalADC_3] = PA3,
        [CanalADC_4] = PA4,
        [CanalADC_5] = PA5,
        [CanalADC_6] = PA6,
        [CanalADC_7] = PA7,
        [CanalADC_8] = PB0,
        [CanalADC_9] = PB1,
    };
    static const unsigned numPines = sizeof(pinDeCanal)/sizeof(*pinDeCanal);
    if(canal >= CanalADC_INVALIDO) return;
    
    if(canal <= numPines){
        Pin_configuraEntrada(pinDeCanal[canal],ANALOGICO); // Habilita reloj de GPIO y configura Pin
    }
    ajustaDivADC();

    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;   
    
    //Confiuracion del conversor ADC1
    enum{EXTSEL_SW = 0b111};
    ADC1->CR2 =   ADC_CR2_ADON
                | (EXTSEL_SW <<ADC_CR2_JEXTSEL_Pos)
                | (EXTSEL_SW <<ADC_CR2_EXTSEL_Pos);          
    calibraAdc();
    ADC1->SQR1 = 0;
    ADC1->SQR3 = canal;
    ADC1->SMPR2 = 0;
    
    //Iniciar la conversión
}

int adc_lee (void){
    if(!(ADC1->CR2 & ADC_CR2_ADON)) return -1;
    
    ADC1->CR2 |= ADC_CR2_ADON;         

    while (!ADC_SR_EOC);     // Espera hasta que la conversión se complete (EOC = 1)

    return ADC1->DR;
}

