#include "puerto_serie.h"
#include "gpio.h"
#include <stm32f1xx.h>

static void configuraPuertoSerie(int baudrate){
    SystemCoreClockUpdate();

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    Pin_configuraSalida(PA9,PUSH_PULL | FUNCION_ALTERNATIVA,V_BAJA);
    Pin_configuraEntrada(PA10,PULL_UP);

    const uint32_t divisor = SystemCoreClock/baudrate;

    if (divisor > 0 && divisor < 0x10000){
        USART1->BRR = (SystemCoreClock + (baudrate+1)/2) / baudrate;
    }else if(divisor){
        USART1->BRR = 0xFFFF;
    }else{
        USART1->BRR = 1;
    }
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void PuertoSerie_init(PuertoSerie *self, Fifo *cola_recepcion, Fifo *cola_transmision, int baudrate){
    self ->cola_recepcion = cola_recepcion;
    self->cola_transmision = cola_transmision;
    configuraPuertoSerie(baudrate);
}

bool PuertoSerie_intentaRecibir (PuertoSerie *self, char *caracter_recibido){
    return Fifo_quita(self->cola_recepcion, caracter_recibido);
}

bool PuertoSerie_intentaTransmitir (PuertoSerie *self, char caracter){
    return Fifo_pon(self->cola_transmision, caracter);
} 

void PuertoSerie_ejecuta (PuertoSerie *self){
    if (USART1->SR & USART_SR_RXNE) {  //Se fija si hay algo en el puerto serie para recibir
        char caracter_recibido = USART1->DR;
        Fifo_pon(self->cola_recepcion, caracter_recibido);    //Si hay algo, lo guarda en la cola de recepcion
    }

    char caracter_a_transmitir;
    if(USART1->SR & USART_SR_TXE){ //Verifica si hay lugar para transmitir
        if(Fifo_quita(self->cola_transmision, &caracter_a_transmitir)){ //Verifica si hay algo para transmitir en la cola de transmision
            USART1->DR = caracter_a_transmitir;
        }
    }
}