#include "gpio.h"
#include "tempo_hw.h"
#include "tempo_ms.h"
#include "paso_a_paso.h"
#include "serie.h"
#include "control_posicion.h"
#include "variable_posicion.h"
#include "control_temperatura.h"
#include "termometro.h"
#include "salida_digital.h"
#include "variable.h"
#include <stdbool.h>


int main(void){

//MOTOR:
    SalidaDigital salida_motor_1;
    SalidaDigital salida_motor_2;
    Motor motor;

    SalidaDigital_init(&salida_motor_1, "pin1_out", PB10);
    SalidaDigital_init(&salida_motor_2, "pin2_out", PB11);

    Motor_init(&motor, salida_motor_1, salida_motor_2);

//CONTROL POSICION
    ControlPosicion controlPos;
    VariablePos posDeseada;
    EntradaDigital finCarreraDentro, finCarreraFuera;

    EntradaDigital_init(&finCarreraDentro, "Fin de Carrera Dentro", PA8, true);
    EntradaDigital_init(&finCarreraFuera, "Fin de Carrera Fuera", PA9, true); 

    VariablePos_init(&posDeseada, CPPosicion_DENTRO, "Posicion Deseada");
    ControlPosicion_init(&controlPos, &posDeseada, &finCarreraDentro, &finCarreraFuera, &motor);

//TERMOMETRO ADC
    CanalADC canal = CanalADC_6;
    Termometro *termometro_adc;
    
    termometro_adc = TermometroADC_init(canal);


//CALEFACTOR:

    SalidaDigital salida_calefactor;
    ControlTemperatura control_temp;
    VariableInt tempDeseada;

    VariableInt_init(&tempDeseada, 25, "Temperatura Deseada");

    SalidaDigital_init(&salida_calefactor, "pin_calefactor", PA1);
    ControlTemperatura_init(&control_temp, termometro_adc, &tempDeseada, &salida_calefactor);

//LOOP PRINCIPAL:

    for(;;){
    
    ControlTemperatura_ejecuta(&control_temp);
    ControlPosicion_ejecuta(&controlPos);

    }
    return 0;
}

