

#ifndef NOISE_MAKER_INSTRUMENT_H
#define NOISE_MAKER_INSTRUMENT_H

#include "note.h"
#include "data_structure/double_pair.h"
#include "data_structure/int64_t_pair.h"
#include "constants.h"

struct instrument
{
    // these notes are mapped to the keyboard
    struct note notes[NOTES_PER_INSTRUMENT];

    struct double_pair volume_panning;

    // determined by the x position of the pointer of this instrument
    double frequency_percent;

    // determined by the y position of the pointer of this instrument
    double volume_percent;

    // number of parts per note
    // the maximum for this value is MAX_NOTE_PARTS
    int parts;

    bool use_custom_shape;

    int sound_shape[MAX_SOUND_SHAPES_PER_INSTRUMENT][DRAW_SPACE_WIDTH];

    int *current_sound_shape;

    double average_frequency;

    double total_notes_volume;
};

typedef struct instrument* not_owned_instrument_pointer;

void
instrument_init(
        struct instrument *instrument
        , struct double_pair volume_panning
);

void
instrument_move_left(struct instrument *instrument, double volume);

void
instrument_move_right(struct instrument *instrument, double volume);

void
instrument_set_volume_and_frequency(
        struct instrument *instrument
        , double volume_percent
        , double frequency_percent
        , bool b
);

void
instrument_play(struct instrument *instrument, int note_index);

void
instrument_release_note(struct instrument *instrument, int note_index);

void
instrument_generate_sample(
        struct instrument *instrument
        , struct int64_t_pair *samples
);

void
instrument_set_parts(
        struct instrument *instrument, int parts
);

void
instrument_move_to(struct instrument *instrument, double position_to_the_right_percent);
#endif //NOISE_MAKER_INSTRUMENT_H
