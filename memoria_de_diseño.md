# Electrónica IV - Proyecto Integrador - Memoria de Diseño
Integrantes: 
+ Juarez, Gustavo Leonel
+ Sonzogni, Facundo
+ Vega Caro, María Ayelén

## 1. Introducción
En este proyecto se empleó un microcontrolador STM32 para desarrollar un dispositivo cuyas funciones principales son la de recibir comandos a través de un puerto serie, que permita manejar la posición de una bandeja para que ingrese o salga de una cavidad la cual se calentará o enfriará, según una temperatura de *setpoint* definida por el usuario.
Se trata de un proyecto conjunto entre dos grupos, de modo que uno de ellos se encarga de configuarar el ingreso de comandos por un teclado y la observación de resultados en una pantalla, mientras que el grupo restante (nuestro grupo) se ocupa de controlar la posicion de la bandeja con dos fines de carrera y un motor de continua, asi como de la medicion de temperatura con un LM35 y una resistencia calefactora para aclimatar la cavidad. La comunicación entre ambos grupos se realiza a través del puerto serie a través del periferico UART.

## 2. 
