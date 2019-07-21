#include <stdio.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>
#include <SDL2/SDL_timer.h>
#include "renderer.h"
#include "logging.h"
#include "input.h"
#include "program.h"
#include "audio.h"


#define frames_per_second 60
#define ms_per_second 1000
#define ms_per_frame (ms_per_second / frames_per_second)

int
main()
{
    logging_trace("Program started.\n");

    renderer_init();
    program_init();
    audio_init();
    input_init();
    FILE *f = fopen("instrument0", "rb");
    fread(audio.instruments[0].sound_shape, sizeof(char), sizeof(audio.instruments[0].sound_shape), f);
    fclose(f);

    uint32_t time_of_last_update = 0;
    logging_trace("Main loop started...\n");
    while (!program.quit)
    {
        uint32_t time = SDL_GetTicks();
        uint32_t ms_since_last_frame = time - time_of_last_update;
        if (ms_since_last_frame > ms_per_frame)
        {
            input_poll();
            renderer_render();
            time_of_last_update = SDL_GetTicks();
        }
        audio_update();
    }
    logging_trace("Exited main loop.\n");

    renderer_destroy();

    f = fopen("instrument0", "wb");
    fwrite(audio.instruments[0].sound_shape, sizeof(int), sizeof(audio.instruments[0].sound_shape), f);
    fclose(f);

    return 0;
}