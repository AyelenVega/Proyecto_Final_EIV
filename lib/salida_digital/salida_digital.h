#ifndef SALIDA_DIGITAL_H
#define SALIDA_DIGITAL_H

typedef struct SalidaDigital{
  int estado;
  const char* nombre;
}SalidaDigital;

void SalidaDigital_init(SalidaDigital *self,const char *nombre);
void SalidaDigital_enciende(SalidaDigital *self);
void SalidaDigital_apaga(SalidaDigital *self);

#endif
