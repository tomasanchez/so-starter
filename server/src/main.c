/**
 * main.c
 *
 * @file  Módulo
 * @author Tomás A. Sánchez and R. Nicolás Savinelli
 * @since  03.17.2022
 */

#include "lib.h"
#include "log.h"
#include "cfg.h"
#include "server.h"
#include "main.h"
#include "routines.h"
#include "thread_manager.h"
#include "signals.h"

servidor_t g_server;

static int _init(servidor_t *server)
{
	if (log_init(LOG_FILE, MODULE_NAME, true) == ERROR)
		return LOG_INITIALIZATION_ERROR;

	if (config_init(CONF_FILE) == ERROR)
	{
		LOG_ERROR("No se pudo levantar la configuracion.");
		return CONFIGURATION_INITIALIZATION_ERROR;
	}

	thread_manager_init();

	/* BO initialization routines */

	/* EO initialization routines */

	signals_init();

	*server = servidor_create(ip(), puerto());

	return EXIT_SUCCESS;
}

static int _run(servidor_t *server)
{
	if (servidor_escuchar(server) == -1)
	{
		LOG_ERROR("No se pudo levantar el servidor.");
		return SERVER_RUNTIME_ERROR;
	}

	LOG_DEBUG("Servidor a la espera de clientes...");

	for (;;)
		servidor_run(server, routine);

	return EXIT_SUCCESS;
}

void stop(servidor_t *server, int exit_code)
{
	LOG_DEBUG("Finalizando ejecucion.\n");

	thread_manager_end();

	servidor_destroy(server);

	/* BO finalization routines */

	/* EO finalization routines */

	config_close();

	log_close();

	exit(exit_code);
}

int main(void)
{
	int exit_code = _init(&g_server);

	if (exit_code == EXIT_SUCCESS)
		exit_code = _run(&g_server);

	stop(&g_server, exit_code);
}
