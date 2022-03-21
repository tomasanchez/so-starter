/**
 * main.c
 *
 * @file  Módulo
 * @author Tomás A. Sánchez and R. Nicolás Savinelli
 * @since  03.17.2022
 */

#include "core.functionality.h"
#include "module.procedures.h"

int main(void)
{
    if (init() == SUCCESS)
    {
        if (start() == SUCCESS)
        {
            run(procedures);
        }
    }

    stop(SUCCESS);
}