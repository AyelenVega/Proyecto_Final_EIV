#include "gpio.h"
#include "tempo_hw.h"
#include "tempo_ms.h"
#include "paso_a_paso.h"
#include "serie.h"
#include "control_posicion.h"
#include "variable_posicion.h"
#include "control_temperatura.h"
#include "termometro.h"
#include "salida_digital.h"
#include "variable.h"
#include <stdbool.h>


int main(void){

    ControlTemperatura controlTemp;
    SalidaDigital calefactor;
    VariableInt tempDeseada;
    Termometro *termometroADC;
    CanalADC canalT = CanalADC_0;

    termometroADC = TermometroADC_init(canalT);
    ControlTemperatura_init(&controlTemp,termometroADC,&tempDeseada,&calefactor);

    for(;;){
        
    }

    return 0;
}

