#include "comando.h"

extern inline const char * ContextoComando_obtNombre(ContextoComando *self);
extern inline const char * ContextoComando_obtParametro(ContextoComando *self);
extern inline int ContextoComando_transmiteCadena(ContextoComando *self, const char* cadena);
extern inline void Comando_ejecuta(Comando *self,ContextoComando *ctx);
