#include <portaudio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <data_structure/int64_t_pair.h>
#include "audio.h"
#include "logging.h"
#include "note.h"
#include "input.h"
#include "program.h"
#include "renderer.h"
#include "instrument.h"

struct audio audio;

PaStreamParameters outputParameters;
PaStream *stream;

const uint32_t TABLE_SIZE = 4096;

struct audio_data
{
    int16_t *circular_buffer;
    int read_end;
    int write_end;
};


struct audio_data audio_data;

static int
portaudio_callback(
        const void *input_buffer
        , void *output_buffer
        , unsigned long frames_per_buffer
        , const PaStreamCallbackTimeInfo *time_info
        , PaStreamCallbackFlags status_flags
        , void *user_data
)
{
    struct audio_data *data = (struct audio_data *) user_data;
    int16_t *out = (int16_t *) output_buffer;

    for (int i = 0; i < frames_per_buffer; ++i)
    {
        *out++ = data->circular_buffer[data->read_end];

        data->read_end++;
        if (data->read_end >= TABLE_SIZE)
        {
            data->read_end = 0;
        }

        *out++ = data->circular_buffer[data->read_end];

        data->read_end++;
        if (data->read_end >= TABLE_SIZE)
        {
            data->read_end = 0;
        }
    }


    return paContinue;
}

int
audio_init()
{
    logging_trace("Initializing audio system...");


    audio_data.circular_buffer = malloc(TABLE_SIZE * sizeof(int16_t));
    audio_data.read_end = 0;
    audio_data.write_end = 0;

    PaError err;
    err = Pa_Initialize();
    if (err == paNoError)
    {
        logging_trace("PortAudio initialized.\n");
    }
    else
    {
        logging_trace("Error during initialization of PortAudio., %d\n", err);
        return 1;
    }

    outputParameters.device = Pa_GetDefaultOutputDevice();
    if (outputParameters.device == paNoDevice)
    {
        logging_trace("No device found!\n");
        return 1;
    }
    else
    {
        logging_trace("Found default output device.\n");
    }
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paInt16;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(
            outputParameters.device
    )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
            &stream
            , NULL
            , &outputParameters
            , SAMPLE_RATE
            , paFramesPerBufferUnspecified
            , paClipOff // we won't output out of range samples so don't bother clipping them
            , portaudio_callback
            , &audio_data
    );

    if (err == paNoError)
    {
        logging_trace("PortAudio stream opened.\n");
    }
    else
    {
        logging_trace("Error when opening PortAudio stream.\n");
        return 1;
    }

    err = Pa_StartStream(stream);
    if (err == paNoError)
    {
        logging_trace("PortAudio stream started.\n");
    }
    else
    {
        logging_trace("Error when starting PortAudio stream.\n");
    }
    audio_init_note_frequencies_and_volume();

    logging_trace("Audio system initialized.");

    logging_trace("Initializing instruments...");
    struct double_pair instrument0_panning;
    instrument0_panning.data[0] = 1.0;
    instrument0_panning.data[1] = 0.0;
    instrument_init(&audio.instruments[0], instrument0_panning);

    struct double_pair instrument1_panning;
    instrument1_panning.data[0] = 0.0;
    instrument1_panning.data[1] = 1.0;
    instrument_init(&audio.instruments[1], instrument1_panning);
    logging_trace("Instruments initialized.");

    return 0;
}


void
audio_update()
{
    while (audio_data.write_end != audio_data.read_end)
    {
        struct int64_t_pair samples;
        samples.data[0] = 0;
        samples.data[1] = 0;
        for (int i = 0; i < NUMBER_INSTRUMENTS; i++)
        {
            instrument_generate_sample(&audio.instruments[i], &samples);
        }

        audio_data.circular_buffer[audio_data.write_end] = (int16_t) samples.data[0];
        ++audio_data.write_end;
        if (audio_data.write_end == TABLE_SIZE)
        {
            audio_data.write_end = 0;
        }

        audio_data.circular_buffer[audio_data.write_end] = (int16_t) samples.data[1];
        ++audio_data.write_end;
        if (audio_data.write_end == TABLE_SIZE)
        {
            audio_data.write_end = 0;
        }
    }
}

void
audio_init_note_frequencies_and_volume()
{
    for (int i = 0; i < NUMBER_INSTRUMENTS; i++)
    {
        instrument_set_volume_and_frequency(
                &audio.instruments[i],
                (program.pointers[i].y / (renderer.window_size.y * 1.0)) * 8.0,
                program.pointers[i].x / (renderer.window_size.x * 1.0) * 1.1
        );
    }
    program.attack_frames = program.pointers[1].y + 1;
    program.decay_frames = program.pointers[1].x + 1;
}