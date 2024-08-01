#ifndef INTERPRETE_H
#define INTERPRETE_H
#include "puerto_serie.h"
#include "diccionario_comandos.h"
#include <ctype.h>

enum{
    MAX_CARACTERES_NOM = 10,
    MAX_CARACTERES_PARAM = 5  
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
}Interprete;

void Interprete_init(Interprete *self, PuertoSerie *puerto);
void Interprete_ejecuta(Interprete *self);

#endif