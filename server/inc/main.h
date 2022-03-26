/**
 * main.h
 *
 * @file Core definitions for the server module
 * @author Tomás A. Sánchez and R. Nicolás Savinelli
 * @since  03.17.2022
 */

#pragma once

#include "server.h"

#define MODULE_NAME "server"

#define LOG_FILE "server.log"
#define CONF_FILE "server.cfg"

void stop(servidor_t *server, int exit_code);
