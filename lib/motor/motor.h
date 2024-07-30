#ifndef MOTOR_H
#define MOTOR_H
#include "salida_digital.h"

typedef enum Motor_Estado {
    Motor_Estado_ENCENDIDO_INGRESO,
    Motor_Estado_ENCENDIDO_SALIDA,
    Motor_Estado_APAGADO
}Motor_Estado;

typedef struct Motor{
    Motor_Estado estadoMotor;
    SalidaDigital motor_1;
    SalidaDigital motor_2;
}Motor;

void Motor_init(Motor *self, SalidaDigital motor_1, SalidaDigital motor_2);
void Motor_ingreso(Motor *self);
void Motor_salida(Motor *self);
void Motor_apaga(Motor *self);


#endif 