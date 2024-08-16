#ifndef DICCIONARIO_COMANDOS_H
#define DICCIONARIO_COMANDOS_H
#include "comando.h"

typedef struct EntradaDiccionarioComandos{
    const char* nombre;
    Comando* comando;
}EntradaDiccionarioComandos;

typedef struct DiccionarioComandos{
    int num_comandos;
    const EntradaDiccionarioComandos* comandos;
}DiccionarioComandos;

/**
 * @brief Inicializa el diccionario de comandos
 * 
 * @param self puntero a struct DiccionarioComandos
 * @param num_comandos cantidad de comandos que tendra el diccionario
 * @param comandos puntero a struct EntradaDiccionarioComandos
 */
void DiccionarioComandos_init(DiccionarioComandos* self, int num_comandos, const EntradaDiccionarioComandos* comandos);

/**
 * @brief Obtiene un comando de diccionario comandos
 * 
 * @param self puntero a struct DiccionarioComandos
 * @param nombre nombre del comando
 * @retval Comando* 
 */
Comando* DiccionarioComandos_obtComando(DiccionarioComandos* self, const char* nombre);

#endif