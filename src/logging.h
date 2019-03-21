

#ifndef NOISE_MAKER_LOGGING_H
#define NOISE_MAKER_LOGGING_H

#include <time.h>
#include <stdio.h>


void
_logging_trace(char *file_name, int line_number, const char *format, ...);

#define logging_trace(format, ...) _logging_trace(__FILE__, __LINE__, format, ##__VA_ARGS__)
#endif //NOISE_MAKER_LOGGING_H
