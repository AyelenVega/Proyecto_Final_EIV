#include "interprete.h"

static bool esTerminador(char caracter){
    return (caracter == '\n'|| caracter == '\r'); 
}

static void ejecutaComando(Interprete *self){

}

void Interprete_init(Interprete *self, PuertoSerie *puerto){
    self->estado = CargaNombre;
    self->indice = 0;
    self->nombre[0] = 0;
    self->parametro[0] = 0;
    self->puerto = puerto;
}

void Interprete_ejecuta(Interprete *self)
{
    char caracter;
    if(PuertoSerie_intentaRecibir(self->puerto, &caracter) == false) return;

    switch (self->estado)
    {
    case CargaNombre:
        if(isgraph(caracter) && self->indice < (MAX_CARACTERES_NOM -1)){
            self->nombre[self->indice] = caracter;
            self->indice ++;
        } else if (esTerminador(caracter) && self-> indice > 0){
            ejecutaComando(self);
            self->indice = 0;
            self->nombre[0] = 0;
            self->parametro[0] = 0;
        } else if (isspace(caracter) && self->indice > 0){
            self->nombre[self->indice] = 0;
            self->indice = 0;
            self->estado = CargaParametro;
        }
    break; case CargaParametro:
        if(isgraph(caracter) && self->indice < (MAX_CARACTERES_PARAM - 1)){
            self->parametro[self->indice] = caracter;
            self->indice ++;
        } else if(esTerminador(caracter)){
            ejecutaComando(self);
            self->nombre[0] = 0;
            self->parametro[0] = 0;
            self->indice = 0;
            self->estado = CargaNombre;
        }
    break; default:
    //Esto es un error
    break;
    }
}

