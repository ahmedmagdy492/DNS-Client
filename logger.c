#include "logger.h"
#define LOG 0

void log_msg(const char* msg)
{
    #if LOG == 1
    printf("dns client: %s\n", msg);
    #endif
}