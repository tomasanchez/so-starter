/**
* cfg.h
*
* @file API de configuraciones
* @author Tomás Sánchez
* @since  09.11.2021
*/

#pragma once

#include <string.h>
#include "lib.h"

// ============================================================================================================
//                                   ***** Funciones Públicas  *****
// ============================================================================================================

// -----------------------------------------------------------
//  Constructor y Destructor
// ------------------------------------------------------------

/**
 * Levanta el archivo configuraciones de la carpeta config/.
 * 
 * @param path el Nombre del archivo de configuraciones
 * @return SUCCESS o ERROR
 */
int config_init(char *path);

/**
 * Pregunta si la configuracion fue inicializada.
 * 
 * @return SUCCESS o ERROR
 */
int config_initialized(void);

/**
 * Destruye la configuración cargada.
 */
void config_close(void);

/**
 * @brief Obtiene la instancia del singleton
 * 
 * @return la referencia a la configuracion
 */
void *config_instance(void);

// -----------------------------------------------------------
//  Puertos
// ------------------------------------------------------------

/**
 * Lee el valor de la key puerto de la config.
 * 
 * @return el puerto propiamente dicho
 */
char *puerto(void);

// -----------------------------------------------------------
//  IPs
// ------------------------------------------------------------

/**
 * Lee el valor de la key IP de la config.
 * 
 * @return el IP correspondiente
 */
char *ip(void);

// -----------------------------------------------------------
//  Módulo Memoria
// ------------------------------------------------------------

/**
 * Lee el valor de la key del tamanio de meoria de la config 
 * 
 * @returns el tamanio de memoria a utilizar
 */
int tamanio_memoria(void);

/**
 * Lee el valor de la key del tipo de asignacion de la config 
 * 
 * @returns el tipo de asignacion a utilizar
 */
char *tipo_de_asignacion(void);

/**
 * Lee el valor de la key del algoritmo de reemplazo de la mmu de la config 
 * 
 * @returns el algoritmo de reemplazo de la mmu a utilizar
 */
char *algoritmo_de_reemplazo_mmu(void);

/**
 * Lee el valor de la key de la cantidad de entradas de la tlb de la config 
 * 
 * @returns la cantidad de entradas de la tlb a utilizar
 */
int cantidad_de_entradas_tlb(void);

/**
 * Lee el valor de la key del algoritmo de reemplazo de la tlb de la config 
 * 
 * @returns el algoritmo de reemplazo de la tlb a utilizar
 */
char *algoritmo_de_reemplazo_tlb(void);

/**
 * Lee el valor de la key del retardo de acierto de la tlb de la config 
 * 
 * @returns el retardo de acierto de la tlb a utilizar
 */
int retardo_de_acierto_tlb(void);

/**
 * Lee el valor de la key del retardo de fallo de la tlb de la config 
 * 
 * @returns el retardo de fallo de la tlb a utilizar
 */
int retardo_de_fallo_tlb(void);

/**
 * Lee el valor de la key del tamaño de página de la config 
 * 
 * @returns el tamaño de página a utilizar
 */
int tamanio_pagina(void);

/**
 * Lee el valor de la key de los marcos maximos de la config 
 * 
 * @returns el maximo de marcos a utilizar
 */
int marcos_maximos(void);
