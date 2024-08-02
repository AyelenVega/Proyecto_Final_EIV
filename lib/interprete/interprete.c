#include "interprete.h"
#include "container_of.h"

static bool esTerminador(char caracter){
    return (caracter == '\n'|| caracter == '\r'); 
}

static const char *obtNombre(ContextoComando *contexto_comando)
{
    Interprete *const self = container_of(contexto_comando,Interprete,contexto_comando);
    return self->nombre;
}
static const char *obtParametro(ContextoComando *contexto_comando)
{
    Interprete *const self = container_of(contexto_comando,Interprete,contexto_comando);
    return self->parametro;
}

static int transmiteCadena(Interprete *self, const char* cadena)
{
    int cuenta=0;
    for (const char *p = cadena; *p != 0; p++){
        if(!PuertoSerie_intentaTransmitir(self->puerto, *p)) break;
        ++cuenta;
    }
    return cuenta;
}

static int implTransmiteCadena(ContextoComando *contexto_comando, const char* cadena)
{
    Interprete *const self = container_of(contexto_comando,Interprete,contexto_comando);
    return transmiteCadena(self,cadena);
}

static void ejecutaComando(Interprete *self){
    Comando *comando;
    comando = DiccionarioComandos_obtComando(self->comandos, self->nombre);

    if(comando != NULL){
        Comando_ejecuta(comando, &self->contexto_comando);
    }else{
        transmiteCadena(self, "ERROR: Comando Invalido\n");
    }
}

static void limpiaComando(Interprete *self)
{
    self->indice = 0;
    self->nombre[0] = 0;
    self->parametro[0] = 0;
}
void Interprete_init(Interprete *self, PuertoSerie *puerto, DiccionarioComandos *comandos){
    static const ContextoComando_VT contexto_comando_vt={
        .obtNombre = obtNombre,
        .obtParametro = obtParametro,
        .transmiteCadena = implTransmiteCadena
    };
    self->contexto_comando.vptr_= &contexto_comando_vt;
    self->estado = CargaNombre;
    self->puerto = puerto;
    self->comandos = comandos;
    limpiaComando(self);
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
            self->nombre[self->indice] = 0;
            ejecutaComando(self);
            limpiaComando(self);
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
            self->parametro[self->indice]=0;
            ejecutaComando(self);
            limpiaComando(self);
            self->estado = CargaNombre;
        }
    break; default:
    //Esto es un error
    break;
    }
}

