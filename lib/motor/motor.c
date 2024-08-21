#include "motor.h"
#include <stdio.h>

void Motor_init(Motor *self, SalidaDigital motor_1, SalidaDigital motor_2){
    self->estadoMotor = Motor_Estado_APAGADO;
    self->motor_1 = motor_1;
    self->motor_2 = motor_2;
}

void Motor_ingreso(Motor *self){
    self->estadoMotor = Motor_Estado_ENCENDIDO_INGRESO;
    SalidaDigital_enciende(&(self->motor_1));
    SalidaDigital_apaga(&(self->motor_2));
    
}

void Motor_salida(Motor *self){
    self->estadoMotor = Motor_Estado_ENCENDIDO_SALIDA;
    SalidaDigital_apaga(&(self->motor_1));
    SalidaDigital_enciende(&(self->motor_2));
}

void Motor_apaga(Motor *self){
    self->estadoMotor = Motor_Estado_APAGADO;
    SalidaDigital_apaga(&(self->motor_1));
    SalidaDigital_apaga(&(self->motor_2));
}

