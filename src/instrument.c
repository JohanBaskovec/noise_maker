#include "instrument.h"
#include "logging.h"
#include <math.h>

void
instrument_init(
        struct instrument *instrument
        , struct double_pair volume_panning
)
{
    instrument->frequency_percent = 0;
    instrument->volume_panning = volume_panning;
    instrument->parts = 1;

    for (int i = 0; i < NOTES_PER_INSTRUMENT; i++)
    {
        struct note *note = &instrument->notes[i];
        note_init(note, instrument, i);
        note->max_volume.data[0] = instrument->volume_panning.data[0];
        note->max_volume.data[1] = instrument->volume_panning.data[1];
    }

    instrument->use_custom_shape = true;
    double delta = (2 * M_PI) / DRAW_SPACE_WIDTH;
    for (int j = 0; j < MAX_SOUND_SHAPES_PER_INSTRUMENT; ++j)
    {
        for (int x = 0; x < DRAW_SPACE_WIDTH; x++)
        {
            instrument->sound_shape[j][x] =
                    (int) (sin(delta * x) * (DRAW_SPACE_HEIGHT / 2) +
                           (DRAW_SPACE_HEIGHT / 2));
        }
    }
    instrument->current_sound_shape = instrument->sound_shape[0];
    for (int k = 0; k < DRAW_SPACE_WIDTH; ++k)
    {
        printf("%d\n", instrument->current_sound_shape[k]);
    }
}

void
instrument_move_right(struct instrument *instrument, double volume)
{
    instrument_move_left(instrument, -volume);
}

void
instrument_move_left(struct instrument *instrument, double volume)
{
    instrument->volume_panning.data[0] += volume;
    instrument->volume_panning.data[1] -= volume;

    if (instrument->volume_panning.data[0] > 1.0)
    {
        instrument->volume_panning.data[0] = 1.0;
    }
    else if (instrument->volume_panning.data[0] < 0)
    {
        instrument->volume_panning.data[0] = 0;
    }
    if (instrument->volume_panning.data[1] > 1.0)
    {
        instrument->volume_panning.data[1] = 1.0;
    }
    else if (instrument->volume_panning.data[1] < 0)
    {
        instrument->volume_panning.data[1] = 0;
    }
    logging_trace("Changed left balance. Volume left: %lf, volume right: %lf\n"
                  , instrument->volume_panning.data[0]
                  , instrument->volume_panning.data[1]);
}

void
instrument_set_volume_and_frequency(
        struct instrument *instrument
        , double volume_percent
        , double frequency_percent
)
{
    instrument->frequency_percent = frequency_percent;
    instrument->volume_percent = volume_percent;

    for (int i = 0; i < NOTES_PER_INSTRUMENT; i++)
    {
        if (instrument->notes[i].on)
        {
            note_set_target_frequency(&instrument->notes[i]);
        }
    }
}

void
instrument_play(struct instrument *instrument, int note_index)
{
    note_play_new(&instrument->notes[note_index]);
}

void
instrument_release_note(struct instrument *instrument, int note_index)
{
    note_stop(&instrument->notes[note_index]);
}

void
instrument_generate_sample(
        struct instrument *instrument
        , struct int64_t_pair *samples
)
{
    int64_t sample = 0;

    for (int i = 0; i < NOTES_PER_INSTRUMENT; i++)
    {
        if (instrument->notes[i].on)
        {
            sample += (note_create_sample(&instrument->notes[i]));
        }
    }
    samples->data[0] += (int64_t) (((int16_t) sample) *
                                   instrument->volume_panning.data[0]);
    samples->data[1] += (int64_t) (((int16_t) sample) *
                                   instrument->volume_panning.data[1]);
}

void
instrument_set_parts(
        struct instrument *instrument, int parts
)
{
    instrument->parts = parts;
}
