#ifndef FIFO_H
#define FIFO_H
#include <stdbool.h>

/**
 * @brief define el objeto Fifo
 * 
 */
typedef struct Fifo
{
    int cant_elementos;
    char *base;
    int lectura;
    int escritura;
    bool lleno;
}Fifo;

/**
 * @brief inicializa la cola FIFO de caracteres
 * 
 * @param self puntero a struct Fifo
 * @param cant_elementos  capacidad del buffer
 * @param base puntero al buffer
 */
void Fifo_init(Fifo *self, int cant_elementos, char *base);

/**
 * @brief pone un caracter en la cola
 * 
 * @param self puntero a struct Fifo
 * @param caracter caracter que se pone en la cola
 * @retval true si es posible poner el caracter en la cola
 * @retval false si no es posible poner el caracter en la cola
 */
bool Fifo_pon (Fifo *self, char caracter);

/**
 * @brief quita un caracter de la cola
 * 
 * @param self puntero a struct Fifo
 * @param caracter caracter recuperado
 * @retval true si es posible quitar el caracter
 * @retval false si no es posible quitar el caracter
 */
bool Fifo_quita (Fifo *self, char *caracter);


#endif