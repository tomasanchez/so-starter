/**
 * servidor.h
 *
 * @file API de la iMongo Store
 * @author Tomás Sánchez
 * @since  05.02.2021
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

#define CONF_FILE "server.cfg"

#define RUNNING true

// ============================================================================================================
//                                   ***** Funciones Públicas  *****
// ============================================================================================================

// ------------------------------------------------------------
//  Lifecycle methods
// ------------------------------------------------------------

/**
 * @brief Se llama al Inicializar un modulo
 *
 * @return SUCCESS o bien ERROR
 */
int on_init(void);

/**
 * @brief Realiza el cierre liberando los recursos.
 *
 * @return EXIT_SUCCESS o la SIGNAL correspondiente
 */
int on_before_exit(void);

/**
 * @brief Event hanlder, cuando el servidor se encuentra atendiendo clientes
 *
 * @return ERROR o SUCCESS
 */
int on_client_run(void);

/**
 * @brief Event handler de establecer conexion
 *
 * @param conexion referencia a una conexion
 * @param offline_mode si trabaja sin conexion
 * @return SUCCESS o ERROR
 */
int on_connect(void *conexion, bool offline_mode);

/**
 * @brief Event handler para leer a traves de Readline, al recibir EMPTY_STRING cambia el status
 *
 * @param line la linea leida
 * @param status el estado del proceso
 * @return la linea leida o NULL
 */
char *on_client_read(char *line, bool *status);

/**
 * @brief Event handler para el envio de mensajes
 *
 * @param conexion
 * @param line
 * @return int
 */
int on_client_send(void *conexion, char *line);
