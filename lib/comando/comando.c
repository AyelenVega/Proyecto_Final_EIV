#include "comando.h"

/**
 * @brief Obtiene el nombre del comando
 * 
 * @param self puntero a struct ContextoComando
 * @return const char*
 */
extern inline const char * ContextoComando_obtNombre(ContextoComando *self);

/**
 * @brief Obtiene el parametro del comando
 * 
 * @param self puntero a struct ContextoComando
 * @return const char* 
 */
extern inline const char * ContextoComando_obtParametro(ContextoComando *self);

/**
 * @brief transmite una cadena de caracteres
 * 
 * @param self puntero a struct ContextoComando
 * @param cadena cadena de caracteres a transmitir
 * @retval 1 si se pudo realizar la transmision
 * @retval 0 si no se pudo realizar la transmision 
 */
extern inline int ContextoComando_transmiteCadena(ContextoComando *self, const char* cadena);

/**
 * @brief Ejecuta el comando
 * 
 * @param self puntero a struct Comando
 * @param ctx puntero a struct ContextoComando
 */
extern inline void Comando_ejecuta(Comando *self,ContextoComando *ctx);
