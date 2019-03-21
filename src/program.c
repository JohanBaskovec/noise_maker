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

    program.sound_drawing_canvas[0].instrument = &audio.instruments[0];
    program.sound_drawing_canvas[0].box.bottom = PLAY_SPACE_HEIGHT;
    program.sound_drawing_canvas[0].box.left = 0;
    box_set_height(&program.sound_drawing_canvas[0].box, DRAW_SPACE_HEIGHT);
    box_set_width(&program.sound_drawing_canvas[0].box, DRAW_SPACE_WIDTH);

    program.sound_drawing_canvas[1].instrument = &audio.instruments[1];
    program.sound_drawing_canvas[1].box.bottom = PLAY_SPACE_HEIGHT;
    program.sound_drawing_canvas[1].box.left = renderer.window_size.x / 2;
    box_set_height(&program.sound_drawing_canvas[1].box, DRAW_SPACE_HEIGHT);
    box_set_width(&program.sound_drawing_canvas[1].box, DRAW_SPACE_WIDTH);

    program.playing_area_box.left = 0;
    program.playing_area_box.bottom = 0;
    box_set_height(&program.playing_area_box, PLAY_SPACE_HEIGHT);
    box_set_width(&program.playing_area_box, renderer.window_size.x);
    logging_trace("Program initialized.");
}