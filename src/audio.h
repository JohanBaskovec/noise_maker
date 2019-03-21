

#ifndef NOISE_MAKER_AUDIO_H
#define NOISE_MAKER_AUDIO_H
#include <math.h>
#include "instrument.h"

struct audio
{
    struct instrument instruments[NUMBER_INSTRUMENTS];
};

extern struct audio audio;

int
audio_init();

void
audio_update();

void
move_instrument_to_the_right(int instrument_index, double volume);

void
move_instrument_to_the_left(int instrument_index, double volume);

void
audio_set_parts(int channel, int parts);

void
audio_init_note_frequencies_and_volume();

void
audio_play_note(int instrument_index, int note_index);

void
audio_release_note(int instrument_index, int note_index);
#endif //NOISE_MAKER_AUDIO_H
