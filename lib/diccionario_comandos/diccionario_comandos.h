#ifndef DICCIONARIO_COMANDOS_H
#define DICCIONARIO_COMANDOS_H



//Clase base ABSTRACTA : Comando
typedef struct Comando Comando;
typedef struct Comando_VT Comando_VT;

struct Comando_VT{};
struct Comando{
    Comando_VT const * vptr_;
};



void comandoEjecuta(Comando *self);
//FIN INTERFZA ABSTRACTA

//IMPLEMENTACION CONCRETA: 


#endif