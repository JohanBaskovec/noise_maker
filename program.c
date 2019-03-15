#include "program.h"
#include "logging.h"
#include "renderer.h"

struct program program;

void
program_init()
{
    logging_trace("Initializing program...");
    program.quit = false;
    program.pointers[1].x = 0;
    program.pointers[1].y = 0;
    program.pointers[2].x = 0;
    program.pointers[2].y = 0;
    logging_trace("Program initialized.");
}