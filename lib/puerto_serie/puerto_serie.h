#ifndef PUERTO_SERIE_H
#define PUERTO_SERIE_H
#include "fifo.h"

/**
 * @brief define el objeto Puerto Serie
 * 
 */
typedef struct PuertoSerie
{
    Fifo *cola_recepcion;
    Fifo *cola_transmision;
}PuertoSerie;

/**
 * @brief inicializa el Puerto Serie
 * 
 * @param self puntero a struct PuertoSerie
 * @param cola_recepcion puntero a la cola de recepcion
 * @param cola_transmision puntero a la cola de transmision
 */
void PuertoSerie_init(PuertoSerie *self, Fifo *cola_recepcion, Fifo *cola_transmision, int tasa_baudios);

/**
 * @brief intenta recibir caracter en la cola de recepcion
 * 
 * @param self puntero a struct PuertoSerie
 * @param caracter_recibido caracter recibido por el puerto
 * @retval true si pudo recibir el caracter
 * @retval false si no pudo recibir el caracter
 */
bool PuertoSerie_intentaRecibir (PuertoSerie *self, char *caracter_recibido);

/**
 * @brief intenta transmitir un caracter de la cola de transmision
 * 
 * @param self puntero a struct PuertoSerie
 * @param caracter caracter a transmitir 
 * @retval true si esposible transmitir el caracter
 * @retval false si no es posible transmitir el caracter
 */
bool PuertoSerie_intentaTransmitir (PuertoSerie *self, char caracter);

/**
 * @brief ejecuta la transmision y/o recepcion
 * 
 * @param self puntero a struct PuertoSerie
 */
void PuertoSerie_ejecuta (PuertoSerie *self);

#endif