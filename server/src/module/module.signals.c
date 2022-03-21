#include <commons/collections/list.h>

#include "core.functionality.h"
#include "thread_manager.h"
#include "module.signals.h"
#include "lib.h"
#include "log.h"

extern t_module this;

static void
sigint_handler()
{
    LOG_WARNING("Se capturó la señal SIGINT");
    stop(SIGINT);
}

static void
sigusr1_handler()
{
    LOG_WARNING("Se capturó la señal SIGUSR1");
}

static void
sigusr2_handler()
{
    LOG_WARNING("Se capturó la señal SIGUSR2");
}

static void __handler(int __sig)
{
    switch (__sig)
    {
    case SIGINT:
        sigint_handler();
        break;

    case SIGUSR1:
        sigusr1_handler();
        break;

    case SIGUSR2:
        sigusr2_handler();
        break;

    default:
        break;
    }
}

inline void signals_init()
{
    signal(SIGINT, __handler);
    signal(SIGUSR1, __handler);
    signal(SIGUSR2, __handler);
}