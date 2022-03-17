/**
* configuraciones.c
*
* @file Facilitaciones del TAD config
* @author Tomás Sánchez
* @since  04.23.2021
*/

#include "cfg.h"
#include <commons/config.h>

// ============================================================================================================
//                               ***** Configuracion -  Definiciones *****
// ============================================================================================================

// La configuración en sí misma, ÉSTA CONFIG
static t_config *this;

// La carpeta contenedora de las configs
#define CONFIG_FOLDER_PATH "../config/"

// ============================================================================================================
//                               ***** Funciones Privadas - Declaraciones *****
// ============================================================================================================

/**
 * Obtiene el key-value de la config.
 *
 * @param key el valor de la key a leer
 * @return el valor string obtenido.
 */
char *config_string(char *key);

/**
 * Obtiene el key-value de la config.
 *
 * @param key el valor de la key a leer
 * @return el valor int obtenido
 */
int config_int(char *key);

/**
 * Obtiene el key-value de la config.
 *
 * @param key el valor de la key a leer
 * @return el valor en array, obtenido.
 */
char **config_array(char *key);

/**
 * Obtiene el key-value de la config.
 *
 * @param key el valor de la key a leer
 * @return el valor double obtenido.
 */
double config_double(char *key);

/**
 * Obtiene el key-value de la config.
 *
 * @param key el valor de la key a leer
 * @return el valor loong obtenido.
 */
long config_long(char *key);

// ============================================================================================================
//                               ***** Funciones Privadas - Definiciones *****
// ============================================================================================================

// -----------------------------------------------------------
//  Getters
// ------------------------------------------------------------

inline char *config_string(char *key)
{
    return config_get_string_value(this, key);
}

inline int config_int(char *key)
{
    return config_get_int_value(this, key);
}

inline char **config_array(char *key)
{
    return config_get_array_value(this, key);
}

inline double config_double(char *key)
{
    return config_get_double_value(this, key);
}

inline long config_long(char *key)
{
    return config_get_long_value(this, key);
}

// ============================================================================================================
//                               ***** Funciones Públicas, Definiciones *****
// ============================================================================================================

// -----------------------------------------------------------
//  Constructor y Destructor
// -----------------------------------------------------------

int config_init(char *path)
{
    // La ruta del directorio contenedor
    char carpeta_contenedora[MAX_CHARS] = CONFIG_FOLDER_PATH;

    if (!this)
        this = config_create(strcat(carpeta_contenedora, path));

    if (this EQ NULL)
    {
        perror("Error:");
        return ERROR;
    }

    return SUCCESS;
}

int config_initialized()
{
    if (this EQ NULL)
    {
        perror("Error:");
        return ERROR;
    }

    return SUCCESS;
}

void config_close(void)
{
    if (this)
        config_destroy(this);

    this = NULL;
}

void *config_instance(void)
{
    return this;
}
// -----------------------------------------------------------
//  Puertos
// ------------------------------------------------------------

// Config-Key Puerto
#define PUERTO_KEY "PUERTO"

inline char *puerto(void)
{
    return config_string(PUERTO_KEY);
}

// -----------------------------------------------------------
//  IPs
// ------------------------------------------------------------

// Config-Key IP

#define IP_KEY "IP"

inline char *ip(void)
{
    return config_string(IP_KEY);
}

// -----------------------------------------------------------
//  Módulo memoria
// ------------------------------------------------------------

#define TAMANIO_KEY "TAMANIO"

inline int tamanio_memoria(void)
{
    return config_int(TAMANIO_KEY);
}

#define TIPO_ASIGNACION_KEY "TIPO_ASIGNACION"

inline char *tipo_de_asignacion(void)
{
    return config_string(TIPO_ASIGNACION_KEY);
}

#define ALGORITMO_REEMPLAZO_MMU_KEY "ALGORITMO_REEMPLAZO_MMU"

inline char *algoritmo_de_reemplazo_mmu(void)
{
    return config_string(ALGORITMO_REEMPLAZO_MMU_KEY);
}

#define CANTIDAD_ENTRADAS_TLB_KEY "CANTIDAD_ENTRADAS_TLB"

inline int cantidad_de_entradas_tlb(void)
{
    return config_int(CANTIDAD_ENTRADAS_TLB_KEY);
}

#define ALGORITMO_REEMPLAZO_TLB_KEY "ALGORITMO_REEMPLAZO_TLB"

inline char *algoritmo_de_reemplazo_tlb(void)
{
    return config_string(ALGORITMO_REEMPLAZO_TLB_KEY);
}

#define RETARDO_ACIERTO_TLB_KEY "RETARDO_ACIERTO_TLB"

inline int retardo_de_acierto_tlb(void)
{
    return config_int(RETARDO_ACIERTO_TLB_KEY);
}

#define RETARDO_FALLO_TLB_KEY "RETARDO_FALLO_TLB"

inline int retardo_de_fallo_tlb(void)
{
    return config_int(RETARDO_FALLO_TLB_KEY);
}

#define TAMANIO_PAGINA_KEY "TAMANIO_PAGINA"

inline int tamanio_pagina(void)
{
    return config_int(TAMANIO_PAGINA_KEY);
}

#define MARCOS_MAXIMOS_KEY "MARCOS_MAXIMOS"

inline int marcos_maximos(void)
{
    return config_int(MARCOS_MAXIMOS_KEY);
}
