#ifndef MOTOR_H
#define MOTOR_H

typedef enum Motor_Estado {
    Motor_Estado_ENCENDIDO_INGRESO,
    Motor_Estado_ENCENDIDO_SALIDA,
    Motor_Estado_APAGADO
}Motor_Estado;

typedef struct Motor{
    Motor_Estado estadoMotor;
    // deberia agregarle salidas digitales si se usa motor de continua
}Motor;

void Motor_init(Motor *self);
void Motor_ingreso(Motor *self);
void Motor_salida(Motor *self);
void Motor_apaga(Motor *self);


#endif 