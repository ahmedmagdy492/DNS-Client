#include "logger.h"

void log_msg(const char* msg)
{
    #ifdef LOG
    printf("dns client: %s\n", msg);
    #endif

    printf("dns client: %s\n", msg);
}