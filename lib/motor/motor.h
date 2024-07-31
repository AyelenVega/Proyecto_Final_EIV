#ifndef MOTOR_H
#define MOTOR_H
#include "salida_digital.h"

/**
 * @brief Estados posibles que puede tener el motor
 * 
 */
typedef enum Motor_Estado {
    Motor_Estado_ENCENDIDO_INGRESO,
    Motor_Estado_ENCENDIDO_SALIDA,
    Motor_Estado_APAGADO
}Motor_Estado;

/**
 * @brief Estructura que define el objeto motor
 * 
 */
typedef struct Motor{
    Motor_Estado estadoMotor;
    SalidaDigital motor_1;
    SalidaDigital motor_2;
}Motor;

/**
 * @brief Inicializa el motor
 * 
 * @param self puntero a struct Motor
 * @param motor_1 Entrada Digital del pin 1 que controla el motor
 * @param motor_2 Entrada Digital del pin 2 que controla el motor
 */
void Motor_init(Motor *self, SalidaDigital motor_1, SalidaDigital motor_2);

/**
 * @brief Enciende el motor en sentido de ingreso de la bandeja
 * 
 * @param self puntero a struct Motor
 */
void Motor_ingreso(Motor *self);

/**
 * @brief Enciende el motor en sentido de salida de la bandeja
 * 
 * @param self puntero a struct Motor
 */
void Motor_salida(Motor *self);

/**
 * @brief Apaga el motor
 * 
 * @param self puntero a struct Motor
 */
void Motor_apaga(Motor *self);


#endif 