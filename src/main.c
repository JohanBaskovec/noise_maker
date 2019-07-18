#include <stdio.h>
#include <SDL2/SDL_events.h>
#include <stdbool.h>
#include "renderer.h"
#include "logging.h"
#include "input.h"
#include "program.h"
#include "audio.h"


int
main()
{
    logging_trace("Program started.\n");

    renderer_init();
    program_init();
    audio_init();
    input_init();
    FILE *f = fopen("instrument0", "rb");
    fread(audio.instruments[0].sound_shape, sizeof(int), sizeof(audio.instruments[0].sound_shape), f);
    fclose(f);
    f = fopen("instrument1", "rb");
    fread(audio.instruments[1].sound_shape, sizeof(int), sizeof(audio.instruments[1].sound_shape), f);
    fclose(f);

    logging_trace("Main loop started...\n");
    while (!program.quit)
    {

        input_poll();
        renderer_render();
        audio_update();
    }
    logging_trace("Exited main loop.\n");

    renderer_destroy();

    f = fopen("instrument0", "wb");
    fwrite(audio.instruments[0].sound_shape, sizeof(int), sizeof(audio.instruments[0].sound_shape), f);
    fclose(f);
    f = fopen("instrument1", "wb");
    fwrite(audio.instruments[1].sound_shape, sizeof(int), sizeof(audio.instruments[1].sound_shape), f);
    fclose(f);

    return 0;
}