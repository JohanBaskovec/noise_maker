#include "program.h"
#include "logging.h"
#include "renderer.h"

struct program program;

void
program_init()
{
    logging_trace("Initializing program...");
    program.quit = false;
    program.pointers[0].x = 0;
    program.pointers[0].y = 0;
    program.pointers[1].x = 0;
    program.pointers[1].y = 0;
    program.pointers[2].x = 0;
    program.pointers[2].y = 0;

    program.sound_drawing_canvas[0].instrument = &audio.instruments[0];
    program.sound_drawing_canvas[0].box.bottom = PLAY_SPACE_HEIGHT + BUTTONS_HEIGHT;
    program.sound_drawing_canvas[0].box.left = 0;
    box_set_height(&program.sound_drawing_canvas[0].box, DRAW_SPACE_HEIGHT);
    box_set_width(&program.sound_drawing_canvas[0].box, DRAW_SPACE_WIDTH);

    for (int i = 0; i < MAX_SOUND_SHAPES_PER_INSTRUMENT; ++i)
    {
        int width = DRAW_SPACE_WIDTH / MAX_SOUND_SHAPES_PER_INSTRUMENT - 2;
        program.sound_drawing_buttons[i].bottom = PLAY_SPACE_HEIGHT;
        program.sound_drawing_buttons[i].left = i * (width) + (1 * i);
        box_set_height(&program.sound_drawing_buttons[i], BUTTONS_HEIGHT);
        box_set_width(&program.sound_drawing_buttons[i], width);
    }

    program.playing_area_box.left = 0;
    program.playing_area_box.bottom = 0;
    box_set_height(&program.playing_area_box, PLAY_SPACE_HEIGHT);
    box_set_width(&program.playing_area_box, renderer.window_size.x);
    logging_trace("Program initialized.");
}