#include "control_temperatura.h"

void ControlTemperatura_init(ControlTemperatura *self,
                             Termometro *termometro,
                             VariableInt *temperaturaDeseada,
                             SalidaDigital *calefactor)
{
    
    self-> temperaturaDeseada = temperaturaDeseada;
    self-> termometro = termometro;
    self-> calefactor = calefactor;
    self-> estado = CTEstado_APAGADO;
};

void ControlTemperatura_ejecuta(ControlTemperatura *self){
    
  const int tempDeseada = VariableInt_obtValor(self->temperaturaDeseada);
  const int tempActual  = Termometro_obtTemperatura(self->termometro);
  const int tempHigh = tempDeseada + 1;
  const int tempLow = tempDeseada - 1;
  
  
  switch(self->estado){
  case CTEstado_APAGADO:
    if(tempActual<tempLow){
        self->estado = CTEstado_ENCENDIDO;
        SalidaDigital_enciende(self->calefactor);
    }else{
        self->estado = CTEstado_APAGADO;
        
    }
  break;
  case CTEstado_ENCENDIDO:
    if(tempActual>tempHigh){
        self->estado = CTEstado_APAGADO;
        SalidaDigital_apaga(self->calefactor);
    }else{
        self->estado = CTEstado_ENCENDIDO;
    }
  break;
  case CTEstado_INACTIVO:
    // no hace nada
  break;
  default:
    // Esto sería un error...
  break;
  }
  
}
    
    
                    
