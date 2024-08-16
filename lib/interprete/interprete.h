#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "puerto_serie.h"
#include "diccionario_comandos.h"
#include <ctype.h>

enum{
    MAX_CARACTERES_NOM = 12,
    MAX_CARACTERES_PARAM = 12  
};

typedef enum {
    CargaNombre,
    CargaParametro
}EstadoInterprete;

typedef struct Interprete{
    char nombre[MAX_CARACTERES_NOM];
    char parametro[MAX_CARACTERES_PARAM];
    EstadoInterprete estado;
    int indice;
    PuertoSerie *puerto;
    DiccionarioComandos *comandos;
    ContextoComando contexto_comando;
}Interprete;

/**
 * @brief Inicializa el interprete
 * 
 * @param self puntero a struct Interprete
 * @param puerto puntero a struct PuertoSerie
 * @param comandos puntero a struct DiccionarioComandos
 */
void Interprete_init(Interprete *self, PuertoSerie *puerto, DiccionarioComandos *comandos);

/**
 * @brief Ejecuta el interprete
 * 
 * @param self puntero a struct Interprete
 */
void Interprete_ejecuta(Interprete *self);

#endif