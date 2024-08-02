#include "definiciones_comandos.h"
#include "container_of.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool esPregunta(const char* cadena)
{
    bool pregunta = false;
    for(int i=0;cadena[i];++i){
        const bool esUltimoCaracter = !cadena[i+1];
        if(esUltimoCaracter && cadena[i] == '?'){
            pregunta = true;
        }
    }
    return pregunta;
}

static const char * describePosicion(CPPosicion pos)
{
  switch (pos){
  case CPPosicion_EN_TRANSITO: return "en transito";
  case CPPosicion_DENTRO: return "dentro";
  case CPPosicion_FUERA: return "fuera";
  default: return "NO VALIDO";
  }
}

static CPPosicion calculaPosicion(ComandoPos *self)
{
    const int finCarreraDentro = EntradaDigital_lee(self->fin_carrera_dentro);
    const int finCarreraFuera  = EntradaDigital_lee(self->fin_carrera_fuera);
    return finCarreraDentro | (finCarreraFuera << 1);
}

static void stempEjecuta(Comando *comando,ContextoComando *ctx)
{
    ComandoStemp *const self = container_of(comando,ComandoStemp,comando);
    if(esPregunta(ContextoComando_obtNombre(ctx))){
        int stemp = VariableInt_obtValor(self->tempDeseada);
        char stemp_char[12];
        snprintf(stemp_char, 12, "%i", stemp);

        ContextoComando_transmiteCadena(ctx, stemp_char);
        ContextoComando_transmiteCadena(ctx, "\n");
    }else{
        int valor = atoi(ContextoComando_obtParametro(ctx));
        VariableInt_ponValor(self->tempDeseada,valor);
        ContextoComando_transmiteCadena(ctx, "OK\n");
    }
}

static void sposEjecuta(Comando *comando, ContextoComando *ctx){
    ComandoSpos *const self = container_of(comando,ComandoSpos,comando);
    bool correcto = false;
    if(esPregunta(ContextoComando_obtNombre(ctx))){
        CPPosicion spos = VariablePos_obtPos(self->posDeseada);
        const char *spos_char = describePosicion(spos);

        ContextoComando_transmiteCadena(ctx, spos_char);
        ContextoComando_transmiteCadena(ctx, "\n");
    }else{
        const char* spos = ContextoComando_obtParametro(ctx);
        if (!strcmp(spos, "dentro"))
        {
            VariablePos_ponPosicion(self->posDeseada, CPPosicion_DENTRO);
            correcto = true;
        }
        else if (!strcmp(spos, "fuera"))
        {
            VariablePos_ponPosicion(self->posDeseada, CPPosicion_FUERA);
            correcto = true;
        }
        ContextoComando_transmiteCadena(ctx, correcto ? "OK\n" : "ERROR\n");   
    }
}

static void tempEjecuta(Comando *comando,ContextoComando *ctx){
    ComandoTemp *const self = container_of(comando,ComandoTemp,comando);
    int temp = Termometro_obtTemperatura(self->termometro);
    char temp_char[12];
    snprintf(temp_char, 12, "%i", temp);
    ContextoComando_transmiteCadena(ctx, temp_char);
    ContextoComando_transmiteCadena(ctx, "\n");
}

static void posEjecuta(Comando *comando,ContextoComando *ctx){
    ComandoPos *const self = container_of(comando,ComandoPos,comando);
    CPPosicion pos = calculaPosicion(self);
    const char * pos_char = describePosicion(pos);

    ContextoComando_transmiteCadena(ctx, pos_char);
    ContextoComando_transmiteCadena(ctx, "\n");    
}

void ComandoStemp_init(ComandoStemp *self, VariableInt *tempDeseada){
    static const Comando_VT comando_vt={
        .comandoEjecuta =stempEjecuta
    };
    
    self->tempDeseada = tempDeseada;
    self->comando.vptr_ = &comando_vt;
}

void ComandoSpos_init(ComandoSpos *self, VariablePos *posDeseada){
    static const Comando_VT comando_vt={
        .comandoEjecuta =sposEjecuta
    };

    self->posDeseada = posDeseada;
    self->comando.vptr_ = &comando_vt;
}

void ComandoPos_init(ComandoPos *self, EntradaDigital *fin_carrera_dentro, EntradaDigital *fin_carrera_fuera){
    static const Comando_VT comando_vt={
        .comandoEjecuta = posEjecuta
    };

    self->fin_carrera_dentro = fin_carrera_dentro;
    self->fin_carrera_fuera = fin_carrera_fuera;
    self->comando.vptr_ = &comando_vt;
}

void ComandoTemp_init(ComandoTemp *self, Termometro *termometro){
    static const Comando_VT comando_vt={
        .comandoEjecuta =tempEjecuta
    };

    self->termometro = termometro;
    self->comando.vptr_ = &comando_vt;
}