

#ifndef NOISE_MAKER_PROGRAM_H
#define NOISE_MAKER_PROGRAM_H

#include <stdbool.h>
#include "vec2f.h"
#include "audio.h"

struct program
{
    bool quit;
    struct vec2i pointers[NUMBER_INSTRUMENTS];
};

extern struct program program;

void
program_init();
#endif //NOISE_MAKER_PROGRAM_H
