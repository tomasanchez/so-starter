/**
 * core.functionality.h
 *
 * @file Core functionality for the server module
 * @author Tomás A. Sánchez and R. Nicolás Savinelli
 * @since  03.17.2022
 */

#pragma once

#include "lib.h"
#include "server.h"

#define RUNNING true

typedef struct MODULE
{
    servidor_t server;
    bool status;
} t_module;

int init(void);

int start(void);

int run(void *(*procedure)(void *));

void stop(int exit_code);