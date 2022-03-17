/**
 * module.c
 *
 * @file  Servidor del Modulo
 * @author R. Nicolás Savinelli
 * @since  05.21.2021
 */

#include "core.functionality.h"
#include "core.definitions.h"

#include "log.h"
#include "cfg.h"
#include "thread_manager.h"

// ============================================================================================================
//                                   ***** Definiciones y Estructuras  *****
// ============================================================================================================

t_module this = {NULL};

// ============================================================================================================
//                                   ***** Funciones Públicas  *****
// ============================================================================================================

int init(void)
{
    if (log_init(LOG_FILE, MODULE_NAME, true) EQ ERROR)
        return ERROR;
    else
        LOG_DEBUG("Inicializando modulo...");

    LOG_DEBUG("Cargando configuracion...");

    if ((config_init(CONF_FILE) EQ ERROR))
    {
        LOG_ERROR("No se pudo levantar las configuraciones");
        log_close();
        return ERROR;
    }

    /* BO initialization routines */

    /* EO initialization routines */

    return SUCCESS;
}

int start(void)
{
    LOG_DEBUG("Inicializando Servidor en %s:%s", ip(), puerto());

    this.server = servidor_create(ip(), puerto());

    return servidor_escuchar(&this.server);
}

int run(void *(*procedure)(void *))
{
    LOG_DEBUG("Servidor a la espera de clientes...");

    this.status = RUNNING;

    for (;;)
        servidor_run(&this.server, procedure);

    return SUCCESS;
}

int stop(void)
{
    this.status = not RUNNING;

    thread_manager_end();
    LOG_DEBUG("Thread manager finalizado.");

    servidor_destroy(&this.server);
    LOG_DEBUG("Servidor terminado.");

    /* BO finalization routines */

    /* EO finalization routines */

    config_close();
    LOG_DEBUG("Configuracion liberada.");

    log_close();

    return SUCCESS;
}
