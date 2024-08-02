#ifndef COMANDO_H
#define COMANDO_H

//INTERFAZ ABSTRACTA: ContextoComando
typedef struct ContextoComando ContextoComando;

typedef struct ContextoComando_VT{
    const char * (*const obtNombre)(ContextoComando *self);
    const char * (*const obtParametro)(ContextoComando *self);
    int (*const transmiteCadena)(ContextoComando *self, const char* cadena);   
}ContextoComando_VT;

struct ContextoComando{
    const ContextoComando_VT *vptr_;
};

inline const char * ContextoComando_obtNombre(ContextoComando *self)
{
    return self->vptr_->obtNombre(self);
}
inline const char * ContextoComando_obtParametro(ContextoComando *self)
{
    return self->vptr_->obtParametro(self);
}
inline int ContextoComando_transmiteCadena(ContextoComando *self, const char* cadena)
{
    return self->vptr_->transmiteCadena(self,cadena);
}   

//FIN INTERFAZ ABSTRACTA: ContextoComando

//INTERFAZ ABSTRACTA : Comando
typedef struct Comando Comando;
typedef struct Comando_VT Comando_VT;

struct Comando_VT{
    void (*const comandoEjecuta)(Comando *self,ContextoComando *ctx);
};

struct Comando{
    Comando_VT const * vptr_;
};

inline void Comando_ejecuta(Comando *self,ContextoComando *ctx)
{
    self->vptr_->comandoEjecuta(self,ctx);
}
//FIN DE INTERFAZ ABSTRACTA: Comando

#endif