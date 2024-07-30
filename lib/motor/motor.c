#include "motor.h"
#include <stdio.h>

/*
    Motor_Estado_ENCENDIDO_INGRESO,
    Motor_Estado_ENCENDIDO_SALIDA,
    Motor_Estado_APAGADO
*/

void Motor_init(Motor *self){
    self->estadoMotor = Motor_Estado_APAGADO;
}

void Motor_ingreso(Motor *self){
    /*printf("Enciende motor en dirección de ingreso\n");
    */
    self->estadoMotor = Motor_Estado_ENCENDIDO_INGRESO;
}

void Motor_salida(Motor *self){
    /*printf("Enciende motor en dirección de salida\n");
    */
    self->estadoMotor = Motor_Estado_ENCENDIDO_SALIDA;
}

void Motor_apaga(Motor *self){
    self->estadoMotor = Motor_Estado_APAGADO;
    /*printf("Apaga motor\n");
    */
}
