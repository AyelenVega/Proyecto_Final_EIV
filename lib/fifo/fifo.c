#include "fifo.h"

void Fifo_init(Fifo *self, int cant_elementos, char *base){
    self->cant_elementos = cant_elementos;
    self->base = base;
    self->lectura = 0;
    self->escritura = 0;
    self->lleno = false;
}

bool Fifo_pon(Fifo *self, char caracter){
    if(self->lleno == true) return false;
    self->base[self->escritura] = caracter;
    self->escritura ++;
    if (self->escritura == self->cant_elementos)
    {
        self->escritura = 0;
    }
    if (self->escritura == self->lectura)
    {
        self->lleno = true;
    }
    return true; 
}

bool Fifo_quita(Fifo *self, char *caracter){
    if (self->escritura == self->lectura && self->lleno == false) return false;
    *caracter = self->base[self->lectura];
    self->lectura ++;
    if (self->lectura == self->cant_elementos)
    {
        self->lectura = 0;
    }
    self->lleno = false;
    return true; 
}
