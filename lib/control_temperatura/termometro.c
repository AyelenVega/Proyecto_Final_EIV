#include "termometro.h"
#include <stdio.h>

void Termometro_init(Termometro *self)
{
  self->temperatura = 25;
}

int Termometro_obtTemperatura(Termometro *self)
{
    const int temperatura = self->temperatura;
    printf("Consulta temperatura actual: %i\n",temperatura);
    return temperatura;
}