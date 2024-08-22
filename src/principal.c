#include "gpio.h"
#include "puerto_serie.h"
#include "control_posicion.h"
#include "control_Temperatura.h"
#include "salida_digital.h"
#include "fifo.h"
#include "definiciones_comandos.h"
#include "diccionario_comandos.h"
#include "interprete.h"
#include <stdbool.h>

static void Init(Interprete *interprete,ControlTemperatura *controlTemp, ControlPosicion *controlPos, PuertoSerie *puerto);  
static PuertoSerie* creaPuertoSerie(int baudrate);

int main(void){
//DEFINICIONES GENERALES

    Interprete interprete;
    ControlTemperatura controlTemp;
    ControlPosicion controlPos;
    PuertoSerie *puerto;

//PUERTO SERIE    

    int baudrate = 9600;  
    puerto = creaPuertoSerie(baudrate);

//INICIALIZACION

    Init(&interprete,&controlTemp,&controlPos,puerto);

//LOOP PRINCIPAL:

    for(;;){
        Interprete_ejecuta(&interprete);
        ControlTemperatura_ejecuta(&controlTemp);
        ControlPosicion_ejecuta(&controlPos);
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

static void Init(Interprete *interprete,ControlTemperatura *controlTemp, ControlPosicion *controlPos, PuertoSerie *puerto){

// MOTOR:

    SalidaDigital salidaMotor1;
    SalidaDigital salidaMotor2;

    Motor motor;

    SalidaDigital_init(&salidaMotor1,"Pin 1 OUT",PB10);    
    SalidaDigital_init(&salidaMotor2,"Pin 2 OUT",PB11);

    Motor_init(&motor,salidaMotor1,salidaMotor2);

// CONTROL POSICION:

    VariablePos posDeseada;
    EntradaDigital finCarreraDentro, finCarreraFuera;

    EntradaDigital_init(&finCarreraDentro, "Fin de Carrera Dentro", PA8, true);
    EntradaDigital_init(&finCarreraFuera, "Fin de Carrera Fuera", PA7, true); 

    VariablePos_init(&posDeseada, CPPosicion_FUERA, "Posicion Deseada");
    ControlPosicion_init(controlPos, &posDeseada, &finCarreraDentro, &finCarreraFuera, &motor);

// TERMOMETRO ADC:

    Termometro *termometroADC;
    CanalADC canalTemp = CanalADC_6;

    termometroADC = TermometroADC_init(canalTemp);

// CALEFACTOR:

    SalidaDigital calefactor;
    VariableInt tempDeseada;

    VariableInt_init(&tempDeseada,0,"Temperatura Deseada");
    SalidaDigital_init(&calefactor,"Pin Calefactor",PA4);

    ControlTemperatura_init(controlTemp,termometroADC,&tempDeseada,&calefactor);


// COMANDOS:

    static ComandoStemp stemp;    
    static ComandoSpos spos;    
    static ComandoTemp temp;    
    static ComandoPos pos;

    ComandoStemp_init(&stemp,&tempDeseada);    
    ComandoSpos_init(&spos,&posDeseada);    
    ComandoTemp_init(&temp,termometroADC);    
    ComandoPos_init(&pos,&finCarreraDentro,&finCarreraFuera);

// DICCIONARIO COMANDOS:

    static const EntradaDiccionarioComandos comandos[]={
        {.nombre = "stemp",  .comando = &stemp.comando},
        {.nombre = "stemp?", .comando = &stemp.comando},
        {.nombre = "spos",   .comando = &spos.comando},
        {.nombre = "spos?",  .comando = &spos.comando},
        {.nombre = "temp?",  .comando = &temp.comando},
        {.nombre = "pos?",   .comando = &pos.comando},
    };
    static const int numComandos = sizeof(comandos)/sizeof(*comandos);
    static DiccionarioComandos diccionarioComandos;

    DiccionarioComandos_init(&diccionarioComandos,numComandos,comandos);

// INTERPRETE:

    Interprete_init(interprete,puerto,&diccionarioComandos);

}
