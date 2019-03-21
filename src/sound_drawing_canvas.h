

#ifndef NOISE_MAKER_SOUND_DRAWING_CANVAS_H
#define NOISE_MAKER_SOUND_DRAWING_CANVAS_H
#include "vec.h"
#include "box.h"
#include <instrument.h>

struct sound_drawing_canvas {
    struct box box;

    not_owned_instrument_pointer instrument;
};
#endif //NOISE_MAKER_SOUND_DRAWING_CANVAS_H
