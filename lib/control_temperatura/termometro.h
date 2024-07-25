#ifndef TERMOMETRO_H
#define TERMOMETRO_H

typedef struct Termometro{
  int temperatura;
}Termometro;

void Termometro_init(Termometro *self);
int Termometro_obtTemperatura(Termometro *self);

#endif
