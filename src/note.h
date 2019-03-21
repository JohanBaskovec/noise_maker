

#ifndef NOISE_MAKER_NOTE_H
#define NOISE_MAKER_NOTE_H

#include <stdbool.h>
#include "data_structure/double_pair.h"
#include "data_structure/int64_t_pair.h"

#define MAX_NOTE_PARTS 5

struct instrument;

struct note
{
    // whether this note produces sound or not
    // (a note can still produce sound after being released)
    bool on;

    // whether this not is released or not
    bool released;

    // frame index on which the note was released
    // is 0 when the note hasn't been released (released is false)
    int released_on_frame;

    // frequency per parts of the note
    // this is semi-random
    //double frequency_per_part[MAX_NOTE_PARTS];

    // volume per part, semi random too
    double volumes_per_part[MAX_NOTE_PARTS];

    double volume;

    // time in frames since the note has been pressed
    int timer_frames;

    // the current volume for each channel
    struct double_pair volume_per_channel;

    // the max volume of each channel
    struct double_pair max_volume;

    // duration of the attack, in frames
    int attack_duration_frame;

    // duration of the decay, in frames
    int decay_duration_frames;


    // note index on the instrument (from lower to higher pitch)
    int index;
    struct instrument *instrument;

    int offset[MAX_NOTE_PARTS];

    double base_frequency[MAX_NOTE_PARTS];

    double instant_frequency[MAX_NOTE_PARTS];

    double target_frequency[MAX_NOTE_PARTS];

    double f_delta[MAX_NOTE_PARTS];

    double delta[MAX_NOTE_PARTS];

    double phase_accumulator[MAX_NOTE_PARTS];

    double sweep_duration_seconds;
};

void
note_init(struct note *note, struct instrument *instrument, int index);

void
note_play_new(struct note *note);

void
note_stop(struct note *note);

int64_t
note_create_sample(struct note *note);

/**
 * Set the target frequency from the note's
 * instrument current frequency_percentage
 * @param note
 */
void
note_set_target_frequency(struct note *note);
#endif //NOISE_MAKER_NOTE_H
