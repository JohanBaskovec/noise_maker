

#ifndef NOISE_MAKER_PROGRAM_H
#define NOISE_MAKER_PROGRAM_H

#include <stdbool.h>
#include "vec.h"
#include "audio.h"
#include "sound_drawing_canvas.h"

struct program
{
    bool quit;
    struct vec2i pointers[NUMBER_INSTRUMENTS];
    struct sound_drawing_canvas sound_drawing_canvas[NUMBER_INSTRUMENTS];
    struct box sound_drawing_buttons[MAX_SOUND_SHAPES_PER_INSTRUMENT * 2];
    struct box playing_area_box;
};

extern struct program program;

void
program_init();
#endif //NOISE_MAKER_PROGRAM_H
