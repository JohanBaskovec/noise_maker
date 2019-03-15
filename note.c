#include <stdint.h>
#include "note.h"
#include "audio.h"
#include "logging.h"
#include <math.h>
#include <stdlib.h>

void
note_init(struct note *note, struct instrument *instrument, int index)
{
    note->index = index;
    note->instrument = instrument;
    note->on = false;
    note->timer_frames = 0;
    note->released = true;
    note->attack_duration_frame = MS_TO_FRAMES(100);
    note->decay_duration_frames = MS_TO_FRAMES(100);
    note->sweep_duration_seconds = 0.01;
}

double
note_compute_part_frequency(
        struct note *note
        , double base_frequency
        , int part_index
)
{
    double frequency_offset_rand = (rand() % 100) / 100.0;
    double frequency_offset =
            (part_index + 1) * 300 * note->instrument->frequency_percent *
            frequency_offset_rand;
    return ((note->index + 1) * base_frequency) +
           frequency_offset;
}


void
note_set_target_frequency(struct note *note)
{
    double base_frequency = 1000 * note->instrument->frequency_percent;
    double target_frequency = note_compute_part_frequency(
            note
            , base_frequency
            , 0
    );
    double diff = target_frequency - note->instant_frequency[0];
    for (int i = 0; i < note->instrument->parts; i++)
    {
        note->target_frequency[i] = note->instant_frequency[i] + diff;
        note->base_frequency[i] = note->instant_frequency[i];
        note->delta[i] = (M_PI * 2) * note->base_frequency[i] / SAMPLE_RATE;
        if (note->sweep_duration_seconds == 0)
        {
            note->f_delta[i] = 0;
        }
        else
        {
            note->f_delta[i] =
                    (note->target_frequency[i] - note->base_frequency[i]) /
                    (SAMPLE_RATE * note->sweep_duration_seconds);
        }
    }
}


void
note_play_new(struct note *note)
{
    note->on = true;
    note->timer_frames = 0;
    note->released = false;
    note->released_on_frame = 0;
    for (int i = 0; i < note->instrument->parts; i++)
    {
        note->delta[i] = 0;
        note->f_delta[i] = 0;
    }

    double base_frequency = 1000 * note->instrument->frequency_percent;

    for (int k = 0; k < note->instrument->parts; k++)
    {
        double frequency = note_compute_part_frequency(note, base_frequency, k);

        note->instant_frequency[k] = frequency;
        note->target_frequency[k] = frequency;
        note->base_frequency[k] = frequency;
    }


    // TODO: maybe do this less randomly, so that pressing the same button
    // multiple time produces the same sound...
    note->volumes_per_part[0] = 1.0 / note->instrument->parts;
    double volume_left = 1 - note->volumes_per_part[0];

    int i = 1;
    for (; i < note->instrument->parts; i++)
    {
        note->volumes_per_part[i] = ((rand() % 100) / 100.0) * volume_left;
        //logging_trace("%lf\n", note->volumes_per_part[i]);
        volume_left -= note->volumes_per_part[i];
        if (volume_left <= 0)
        {
            break;
        }
    }
    for (; i < note->instrument->parts; i++)
    {
        note->volumes_per_part[i] = 0;
    }
}

void
note_stop(struct note *note)
{
    note->released = true;
    note->released_on_frame = note->timer_frames;
}


int64_t
generate_sample_part(struct note *note, double phase_accumulator, double volume)
{
    return (int64_t) (sin(phase_accumulator) * (MAX_SAMPLE_VALUE * volume));
}

int64_t
generate_sample(struct note *note)
{
    int64_t sample = 0;
    for (int i = 0; i < note->instrument->parts; i++)
    {
        sample += generate_sample_part(
                note
                , note->phase_accumulator[i]
                , note->volumes_per_part[i] * note->volume
        );
        note->phase_accumulator[i] += note->delta[i];
        if (fabs(note->instant_frequency[i] - note->target_frequency[i]) >
            0.001)
        {
            note->instant_frequency[i] += note->f_delta[i];
        }
        note->delta[i] = (M_PI * 2) * note->instant_frequency[i] / SAMPLE_RATE;
    }
    return sample;
}


int64_t
note_create_sample(struct note *note)
{
    if (note->released)
    {
        if (note->timer_frames <
            note->released_on_frame + note->decay_duration_frames)
        {
            note->volume = 1.0 -
                           ((note->timer_frames -
                             note->released_on_frame) /
                            (note->decay_duration_frames * 1.0));
        }
        else
        {
            note->on = false;
            return 0;
        }
    }
    else
    {
        if (note->attack_duration_frame > note->timer_frames)
        {
            note->volume =
                    note->timer_frames / (note->attack_duration_frame * 1.0);
        }
        else
        {
            note->volume = 1.0;
        }
    }

    note->volume *= note->instrument->volume_percent;

    int64_t sample = generate_sample(note);
    ++note->timer_frames;
    return sample;
}
