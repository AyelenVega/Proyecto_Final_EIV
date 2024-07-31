#include "gpio.h"
#include "puerto_serie.h"
#include "control_posicion.h"
#include "variable_posicion.h"
#include "control_temperatura.h"
#include "termometro.h"
#include "salida_digital.h"
#include "variable.h"
#include "fifo.h"
#include <stdbool.h>

static PuertoSerie* creaPuertoSerie(int baudrate);

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
    EntradaDigital_init(&finCarreraFuera, "Fin de Carrera Fuera", PA7, true); 

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

//PUERTO SERIE:
    int baudrate = 9600; //[bps]
    char caracter;
    PuertoSerie *puerto;

    puerto = creaPuertoSerie(baudrate);
    for (const char *p = "Prueba\n"; *p != 0; p++){
        PuertoSerie_intentaTransmitir(puerto, *p);
    }

//LOOP PRINCIPAL:

    for(;;){
    
        ControlTemperatura_ejecuta(&control_temp);
        ControlPosicion_ejecuta(&controlPos);
        if (PuertoSerie_intentaRecibir(puerto, &caracter))
        {
            PuertoSerie_intentaTransmitir(puerto,caracter);
        }
        PuertoSerie_ejecuta(puerto);
        
    }
    return 0;
}

static PuertoSerie* creaPuertoSerie(int baudrate){
    static Fifo cola_recepcion;
    static Fifo cola_transmision;
    enum{
        CAPACIDAD_COLA_RECEPCION = 256,
        CAPACIDAD_COLA_TRANSMISION = 256
    };
    static char datos_recepcion[CAPACIDAD_COLA_RECEPCION];
    static char datos_transmision[CAPACIDAD_COLA_TRANSMISION];

    Fifo_init(&cola_recepcion,CAPACIDAD_COLA_RECEPCION, datos_recepcion);
    Fifo_init(&cola_transmision,CAPACIDAD_COLA_TRANSMISION, datos_transmision);
    
    static PuertoSerie puerto;
    PuertoSerie_init(&puerto, &cola_recepcion, &cola_transmision, baudrate);

    return &puerto;
}

