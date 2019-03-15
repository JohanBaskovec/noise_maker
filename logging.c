#include <sys/time.h>
#include <stdarg.h>
#include <time.h>
#include "logging.h"


/**
 * Logs the current date and time in format
 * Year-Month-Day Hour-Minute-Second.Nanosecond
 * followed by the string.
 * @param string The string to log.
 */
void
_logging_trace(char *file_name, int line_number, const char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    char buff[100];
    strftime(buff, sizeof buff, "%F %T", gmtime(&ts.tv_sec));
    printf(" %s.%09ld -> %s:%d -> ", buff, ts.tv_nsec, file_name, line_number);
    vfprintf(stdout, format, argptr);
    printf("\n");
    va_end(argptr);
}