# Electrónica IV - Proyecto Integrador - Memoria de Diseño
Integrantes: 
+ Juarez, Gustavo Leonel
+ Sonzogni, Facundo
+ Vega Caro, María Ayelén

## 1. Introducción
En este proyecto se empleó un microcontrolador STM32 para desarrollar un dispositivo cuyas funciones principales son la de recibir comandos a través de un puerto serie, que permita manejar la posición de una bandeja para que ingrese o salga de una cavidad la cual se calentará o enfriará, según una temperatura de *setpoint* definida por el usuario.
Se trata de un proyecto conjunto entre dos grupos, de modo que uno de ellos se encarga de configuarar el ingreso de comandos por un teclado y la observación de resultados en una pantalla, mientras que el grupo restante (nuestro grupo) se ocupa de controlar la posicion de la bandeja con dos fines de carrera y un motor de continua, asi como de la medicion de temperatura con un LM35 y una resistencia calefactora para aclimatar la cavidad. La comunicación entre ambos grupos se realiza a través del puerto serie a través del periferico UART.

## 2. Diseño

### 2.1 Control de Temperatura

El subsistema de control de temperatura se encarga de mantener la temperatura del dispositivo dentro de un rango deseado. Para ello, utiliza los siguientes componentes:

**Termómetro:**
El termómetro se implementa mediante la librería `termometro`, la cual define una interfaz abstracta `Termometro` y una implementación concreta `TermometroADC` que utiliza el conversor analógico-digital (ADC) del microcontrolador.

La función `TermometroADC_init()` inicializa el termómetro, configurando el canal ADC correspondiente. Para ello, se utiliza la librería `adc`, la cual proporciona funciones para configurar y utilizar el ADC del microcontrolador.
Para inicializar el coversor AD primero se debe configurar cal pin de entrada como entrada analogica.
La frecuencia máxima de conversion establecida por el fabricante es 14MHz, sin embargo, la frecuencia del reloj del bus APB2 puede ser mayor. La función `ajustaDivADC()` (listado 1) se encarga de configurar el divisor de reloj del ADC, de modo que la frecuencia de conversión se mantenga dentro de los límites dados. 


Listado 1

```c
static void ajustaDivADC(void){
    SystemCoreClockUpdate();
    const uint32_t divAPB2 = (RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos;
    const uint32_t relojAPB2 = SystemCoreClock >> ((divAPB2 & 0b100) ? (divAPB2&0b11) + 1 : 0);
    const uint32_t divisorRequerido = ((relojAPB2 + (14000000UL-1)) / 14000000UL);
    const uint32_t configDivisor = (divisorRequerido <= 2) ? 0b00:
                                   (divisorRequerido <= 4) ? 0b01:
                                   (divisorRequerido <= 6) ? 0b10:
                                                             0b11;
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_ADCPRE) | (configDivisor << RCC_CFGR_ADCPRE_Pos);
}
```


Se decidió utilizar el modo de conversión única, la cual se puede iniciar al poner en alto el bit ADON en el registro ADC_CR2 o a través de un disparo externo. Se configuró la conversion para que sea disparada por software, esto se logra configurando los bits de control JEXTSEL del registro ADC_CR2.
El conversor AD necesita un tiempo de estabilización desde que se pone el bit ADON en 1 hasta que pueda empezar a convertir correctamente. Para esperar ese tiempo utilizamos la función `calibraAdc()` (listado 2), la cual no solo nos permite esperar un tiempo antes de comenzar la conversión, sino también realiza un proceso de calibración del ADC, que reduce los errores de medición producidos por variaciones en el banco de capacitores interno.

Listado 2

```c
static void calibraAdc(void){
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while(ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while(ADC1->CR2 & ADC_CR2_CAL);
}
```

En el listado 3 se observa como se realizó la configuración del ADC

Listado 3

```c
void adc_init(CanalADC canal) {
  static const HPin pinDeCanal[]={
        [CanalADC_0] = PA0,
        [CanalADC_1] = PA1,
        [CanalADC_2] = PA2,
        [CanalADC_3] = PA3,
        [CanalADC_4] = PA4,
        [CanalADC_5] = PA5,
        [CanalADC_6] = PA6,
        [CanalADC_7] = PA7,
        [CanalADC_8] = PB0,
        [CanalADC_9] = PB1,
    };
    static const unsigned numPines = sizeof(pinDeCanal)/sizeof(*pinDeCanal);
    if(canal >= CanalADC_INVALIDO) return;
    
    if(canal <= numPines){
        Pin_configuraEntrada(pinDeCanal[canal],ANALOGICO); // Habilita reloj de GPIO y configura Pin
    }
    // Ajustar el divisor de reloj del ADC
    ajustaDivADC();

    // Habilitar el reloj del ADC1
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Configurar el ADC1
    ADC1->CR2 = ADC_CR2_ADON
                | (EXTSEL_SW << ADC_CR2_JEXTSEL_Pos)
                | (EXTSEL_SW << ADC_CR2_EXTSEL_Pos);
    calibraAdc();
    ADC1->SQR1 = 0;
    ADC1->SQR3 = canal;
    ADC1->SMPR2 = 0;
}
```

Finalmente, la función `adc_lee()` (listado 4) realiza una conversión ADC y devuelve el valor leído. Para realizar la conversion se debe volver a poner el bit ADON en alto. La conversión se completa una vez que el bit EOC se pone en alto.

Listado 4

```c
int adc_lee (void){
    if(!(ADC1->CR2 & ADC_CR2_ADON)) return -1;
    
    ADC1->CR2 |= ADC_CR2_ADON;         

    while (!ADC_SR_EOC);     // Espera hasta que la conversión se complete (EOC = 1)

    return ADC1->DR;
}
```

La función `Termometro_obtTemperatura()` de la librería `termometro` utiliza el valor leído del ADC para calcular la temperatura actual del dispositivo.

**Calefactor**:
El calefactor se controla mediante una salida digital, implementada a través de la librería `salida_digital`. La función `SalidaDigital_init()` inicializa la salida digital, asociándola a un pin del microcontrolador y configurando el modo de funcionamiento (push-pull).

Las funciones `SalidaDigital_enciende()` y `SalidaDigital_apaga()` permiten activar y desactivar el calefactor, respectivamente. Estas funciones utilizan las siguientes operaciones de bajo nivel sobre el registro de salida del GPIO correspondiente:

**Control de Temperatura**:
El control de temperatura se implementa en la librería `control_temperatura`. La estructura `ControlTemperatura`  incluye el termómetro, la salida digital del calefactor y la temperatura deseada.

La función `ControlTemperatura_init()` inicializa el sistema de control, asociando los componentes necesarios. La función `ControlTemperatura_ejecuta()` implementa la lógica de control, apagando y encendiendo el calefactor según la temperatura actual y la temperatura deseada:

La lógica de control implementada en esta función mantiene la temperatura dentro de un rango de 1 grado por encima y por debajo de la temperatura deseada, encendiendo y apagando el calefactor según sea necesario. 

Listado 5

```c
void ControlTemperatura_ejecuta(ControlTemperatura *self) {
    const int tempDeseada = VariableInt_obtValor(self->temperaturaDeseada);
    const int tempActual = Termometro_obtTemperatura(self->termometro);
    const int tempHigh = tempDeseada + 1;
    const int tempLow = tempDeseada - 1;

    switch (self->estado) {
        case CTEstado_APAGADO:
            if (tempActual < tempLow) {
                self->estado = CTEstado_ENCENDIDO;
                SalidaDigital_enciende(self->calefactor);
            } else {
                self->estado = CTEstado_APAGADO;
            }
            break;
        case CTEstado_ENCENDIDO:
            if (tempActual > tempHigh) {
                self->estado = CTEstado_APAGADO;
                SalidaDigital_apaga(self->calefactor);
            } else {
                self->estado = CTEstado_ENCENDIDO;
            }
            break;
        default:
            // Error de estado
            break;
    }
}
```


### 2.2 Control de Posición

El subsistema de control de posición se encarga de gestionar la posición de un motor, el cual puede estar en tres estados: dentro, fuera o en tránsito.

**Motor**:
El motor se controla mediante dos salidas digitales, implementadas a través de la librería `salida_digital`. La función `Motor_init()` inicializa el motor, asociando las dos salidas digitales.

Las funciones `Motor_ingreso()`, `Motor_salida()` y `Motor_apaga()` permiten controlar el estado del motor, utilizando las funciones de la librería `salida_digital` 

**Sensores de Posición**:
Los sensores de posición se implementan mediante entradas digitales, utilizando la librería `entrada_digital`. La función `EntradaDigital_init()` inicializa una entrada digital, asociándola a un pin del microcontrolador y configurando el modo de funcionamiento (pull-up o pull-down).

La función `EntradaDigital_lee()` lee el estado de la entrada digital, teniendo en cuenta la configuración del modo de funcionamiento:

**Control de Posición**:
El control de posición se implementa en la librería `control_posicion`. La estructura `ControlPosicion` encapsula el estado del sistema de control, incluyendo la posición deseada, los sensores de posición y el motor.

La función `ControlPosicion_init()` inicializa el sistema de control, asociando los componentes necesarios. La función `ControlPosicion_ejecuta()` implementa la lógica de control, actuando sobre el motor para llevar la posición actual a la posición deseada:

La función `ControlPosicion_calculaPosicion()` se encarga de calcular la posición actual del dispositivo en función de los sensores de posición.

Listado 6 

```c
void ControlPosicion_ejecuta(ControlPosicion *self) {
    const CPPosicion posDeseada = VariablePos_obtPos(self->posDeseada);
    const CPPosicion posActual = ControlPosicion_calculaPosicion(self);

    switch (self->estado) {
        case ControlPosicion_Estado_PARADO:
            if (posActual == CPPosicion_INVALIDA) {
                self->estado = ControlPosicion_Estado_PARADO;
                Motor_apaga(self->motor);
            } else if (posDeseada != posActual) {
                if (posDeseada == CPPosicion_DENTRO) {
                    self->estado = ControlPosicion_Estado_INGRESO;
                    Motor_ingreso(self->motor);
                } else {
                    self->estado = ControlPosicion_Estado_SALIDA;
                    Motor_salida(self->motor);
                }
            }
            break;
        case ControlPosicion_Estado_INGRESO:
            if (posActual == CPPosicion_INVALIDA) {
                self->estado = ControlPosicion_Estado_PARADO;
                Motor_apaga(self->motor);
            } else if (posActual == CPPosicion_DENTRO) {
                self->estado = ControlPosicion_Estado_PARADO;
                Motor_apaga(self->motor);
            }
            break;
        case ControlPosicion_Estado_SALIDA:
            if (posActual == CPPosicion_INVALIDA) {
                self->estado = ControlPosicion_Estado_PARADO;
                Motor_apaga(self->motor);
            } else if (posActual == CPPosicion_FUERA) {
                self->estado = ControlPosicion_Estado_PARADO;
                Motor_apaga(self->motor);
            }
            break;
        default:
            // Error de estado
            break;
    }
}
```


### 2.3 Comunicación

El subsistema de comunicación permite interactuar con el sistema de control a través de un puerto serie.

**Puerto Serie**:
El puerto serie se implementa en la librería `puerto_serie`. La estructura `PuertoSerie` encapsula las colas de recepción y transmisión, así como la configuración del puerto USART1.

La función `PuertoSerie_init()` inicializa el puerto serie, configurando la tasa de baudios y asociando las colas de recepción y transmisión. Para configurar el puerto USART1, se utiliza la funcion del listado 7.

Listado 7

```c
static void configuraPuertoSerie(int baudrate) {
    // Habilitar el reloj del USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // Configurar los pines PA9 y PA10 para USART1 (TX y RX)
    Pin_configuraSalida(PA9, PUSH_PULL | FUNCION_ALTERNATIVA, V_BAJA);
    Pin_configuraEntrada(PA10, PULL_UP);

    // Calcular el divisor de baudrate
    const uint32_t divisor = SystemCoreClock / baudrate;
    if (divisor > 0 && divisor < 0x10000) {
        USART1->BRR = (SystemCoreClock + (baudrate + 1) / 2) / baudrate;
    } else if (divisor) {
        USART1->BRR = 0xFFFF;
    } else {
        USART1->BRR = 1;
    }

    // Configurar el USART1
    USART1->CR2 = 0;
    USART1->CR3 = 0;
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}
```

Las funciones `PuertoSerie_intentaRecibir()` y `PuertoSerie_intentaTransmitir()` permiten la recepción y transmisión de datos, respectivamente, utilizando las colas de recepción y transmisión. La función `PuertoSerie_ejecuta()` gestiona la ejecución del puerto serie.


**Comandos**:
Los comandos se definen en la librería `definiciones_comandos`. Cada comando se implementa como una estructura de la interfaz `Comando`, definida en `comando`. Cada comando define su propia función de ejecución, que se encarga de procesar los parámetros recibidos y actuar sobre el sistema de control.

**Diccionario de Comandos**
El Diccionario de Comandos mantiene un registro de todos los comandos y sus respectivas implementaciones.
Consta de las estructuras `EntradaDiccionarioComandos` y `DiccionarioComandos`, y de las funciones `DiccionarioComandos_init` y `DiccionarioComandos_obtComando` para inicializar el diccionario y obtener un comando específico.

**Interprete**
La librería de Interprete procesa los comandos recibidos a través del puerto serie y ejecuta las acciones correspondientes. Consta de la estructura `Interprete`, que mantiene el estado actual de la interpretación (carga de nombre o parámetro).

La función `Interprete_init` inicializa el intérprete, estableciendo los punteros al puerto serie y al diccionario de comandos.

La función `Interprete_ejecuta` (listado 8) se encarga de procesar los caracteres recibidos del puerto serie. 

Listado 8

```c
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

```

## 3. Conclusiones
El proyecto desarrollado en este documento implementa un sistema de control de temperatura y posición de una bandeja, utilizando un microcontrolador STM32. El sistema consta de varios subsistemas que trabajan en conjunto para lograr el funcionamiento deseado.

El subsistema de control de temperatura utiliza un sensor LM35 para medir la temperatura actual, y un calefactor controlado por una salida digital para mantener la temperatura dentro de un rango cercano a la temperatura de setpoint deseada por el usuario. Este subsistema implementa una lógica de control sencilla pero efectiva, encendiendo y apagando el calefactor según la temperatura medida.

El subsistema de control de posición utiliza dos sensores de posición (fines de carrera) y un motor de continua para mover la bandeja dentro y fuera de la cavidad. Este subsistema implementa una máquina de estados que permite llevar la bandeja a la posición deseada, ya sea dentro o fuera de la cavidad.

Por último, el subsistema de comunicación permite interactuar con el sistema de control a través de un puerto serie, utilizando un intérprete de comandos que procesa los comandos recibidos y ejecuta las acciones correspondientes. 

En general, el proyecto muestra un desarrollo integral de un sistema de control embebido, con una clara separación de responsabilidades entre los diferentes subsistemas y una implementación modular y extensible de cada uno de ellos.













