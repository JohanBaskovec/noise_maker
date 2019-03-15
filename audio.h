

#ifndef NOISE_MAKER_AUDIO_H
#define NOISE_MAKER_AUDIO_H
#include <math.h>
#include "instrument.h"

#define SAMPLE_RATE (44100)
#define BASE_SAMPLES (2.0 * M_PI)
#define BASE_FREQUENCY (SAMPLE_RATE / BASE_SAMPLES)
#define MAX_SAMPLE_VALUE 32767
#define MS_TO_FRAMES(ms) ((int)((ms / 1000.0) * SAMPLE_RATE))
#define FRAMES_TO_MS(frames) ((int)(((frames * 1.0) / (SAMPLE_RATE * 1.0)) * 1000))
#define NUMBER_INSTRUMENTS 2

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
