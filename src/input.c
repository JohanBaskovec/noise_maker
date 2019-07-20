#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include "input.h"
#include "program.h"
#include "logging.h"
#include "audio.h"
#include "renderer.h"

struct input input;

void
draw_in_canvas(struct sound_drawing_canvas *canvas);

enum key key_mapping[SDL_NUM_SCANCODES];
#define MAX_MOUSE_BUTTONS 4
#define MAX_MOUSE_BUTTON_INDEX (MAX_MOUSE_BUTTONS - 1)
enum key mouse_mapping[MAX_MOUSE_BUTTONS];

void
input_init()
{
    key_mapping[SDL_SCANCODE_Q] = KEY_NOTE_LEFT_1;
    key_mapping[SDL_SCANCODE_W] = KEY_NOTE_LEFT_2;
    key_mapping[SDL_SCANCODE_E] = KEY_NOTE_LEFT_3;
    key_mapping[SDL_SCANCODE_R] = KEY_NOTE_LEFT_4;
    key_mapping[SDL_SCANCODE_T] = KEY_NOTE_LEFT_5;
    key_mapping[SDL_SCANCODE_A] = KEY_NOTE_LEFT_6;
    key_mapping[SDL_SCANCODE_S] = KEY_NOTE_LEFT_7;
    key_mapping[SDL_SCANCODE_D] = KEY_NOTE_LEFT_8;
    key_mapping[SDL_SCANCODE_F] = KEY_NOTE_LEFT_9;
    key_mapping[SDL_SCANCODE_G] = KEY_NOTE_LEFT_10;
    key_mapping[SDL_SCANCODE_Z] = KEY_NOTE_LEFT_11;
    key_mapping[SDL_SCANCODE_X] = KEY_NOTE_LEFT_12;
    key_mapping[SDL_SCANCODE_C] = KEY_NOTE_LEFT_13;
    key_mapping[SDL_SCANCODE_V] = KEY_NOTE_LEFT_14;
    key_mapping[SDL_SCANCODE_B] = KEY_NOTE_LEFT_15;
    key_mapping[SDL_SCANCODE_6] = SOUND_SHAPE_SELECTOR_1;
    key_mapping[SDL_SCANCODE_7] = SOUND_SHAPE_SELECTOR_2;
    key_mapping[SDL_SCANCODE_8] = SOUND_SHAPE_SELECTOR_3;
    key_mapping[SDL_SCANCODE_9] = SOUND_SHAPE_SELECTOR_4;
    key_mapping[SDL_SCANCODE_0] = SOUND_SHAPE_SELECTOR_5;
    key_mapping[SDL_SCANCODE_Y] = SOUND_SHAPE_SELECTOR_6;
    key_mapping[SDL_SCANCODE_U] = SOUND_SHAPE_SELECTOR_7;
    key_mapping[SDL_SCANCODE_I] = SOUND_SHAPE_SELECTOR_8;
    key_mapping[SDL_SCANCODE_O] = SOUND_SHAPE_SELECTOR_9;
    key_mapping[SDL_SCANCODE_P] = SOUND_SHAPE_SELECTOR_11;
    key_mapping[SDL_SCANCODE_H] = SOUND_SHAPE_SELECTOR_12;
    key_mapping[SDL_SCANCODE_J] = SOUND_SHAPE_SELECTOR_13;
    key_mapping[SDL_SCANCODE_K] = SOUND_SHAPE_SELECTOR_14;
    key_mapping[SDL_SCANCODE_L] = SOUND_SHAPE_SELECTOR_15;
    key_mapping[SDL_SCANCODE_SEMICOLON] = SOUND_SHAPE_SELECTOR_16;
    key_mapping[SDL_SCANCODE_N] = SOUND_SHAPE_SELECTOR_17;
    key_mapping[SDL_SCANCODE_M] = SOUND_SHAPE_SELECTOR_18;
    key_mapping[SDL_SCANCODE_COMMA] = SOUND_SHAPE_SELECTOR_19;
    key_mapping[SDL_SCANCODE_PERIOD] = SOUND_SHAPE_SELECTOR_20;
    key_mapping[SDL_SCANCODE_SLASH] = SOUND_SHAPE_SELECTOR_21;

    key_mapping[SDL_SCANCODE_ESCAPE] = KEY_EXIT;
    key_mapping[SDL_SCANCODE_1] = KEY_ONE_PART;
    key_mapping[SDL_SCANCODE_2] = KEY_TWO_PART;
    key_mapping[SDL_SCANCODE_3] = KEY_THREE_PART;
    key_mapping[SDL_SCANCODE_4] = KEY_FOUR_PART;
    key_mapping[SDL_SCANCODE_5] = KEY_FIVE_PART;
    key_mapping[SDL_SCANCODE_F1] = KEY_DRAW_MODE_0;


    mouse_mapping[0] = KEY_NONE;
    mouse_mapping[1] = KEY_SELECT_CHANNEL1;
    mouse_mapping[2] = KEY_SELECT_CHANNEL1_AND_2;
    mouse_mapping[3] = KEY_SELECT_CHANNEL2;

    for (int i = 0; i < KEY_ALL; i++)
    {
        input.pressed_keys[i] = false;
        input.previous_pressed_keys[i] = false;
    }

    input.mouse_delta.x = 0;
    input.mouse_delta.y = 0;

    input.move_left_multiplier = 0;
    input.move_right_multiplier = 0;

    unsigned int current_time = SDL_GetTicks();
    input.last_move_left = 0;
    input.last_move_right = 0;
}

void
key_down(enum key key)
{
    if (input.pressed_keys[key])
    {
        return;
    }
    input.pressed_keys[key] = true;
    switch (key)
    {
        case KEY_ONE_PART:
            if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
            {
                instrument_set_parts(&audio.instruments[0], 1);
                instrument_set_parts(&audio.instruments[1], 1);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL1])
            {
                instrument_set_parts(&audio.instruments[0], 1);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL2])
            {
                instrument_set_parts(&audio.instruments[1], 1);
            }
            break;
        case KEY_TWO_PART:

            if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
            {
                instrument_set_parts(&audio.instruments[0], 2);
                instrument_set_parts(&audio.instruments[1], 2);

            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL1])
            {
                instrument_set_parts(&audio.instruments[0], 2);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL2])
            {
                instrument_set_parts(&audio.instruments[1], 2);
            }
            break;

        case KEY_THREE_PART:

            if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
            {
                instrument_set_parts(&audio.instruments[0], 3);
                instrument_set_parts(&audio.instruments[1], 3);

            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL1])
            {
                instrument_set_parts(&audio.instruments[0], 3);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL2])
            {
                instrument_set_parts(&audio.instruments[1], 3);
            }
            break;

        case KEY_FOUR_PART:

            if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
            {
                instrument_set_parts(&audio.instruments[0], 4);
                instrument_set_parts(&audio.instruments[1], 4);

            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL1])
            {
                instrument_set_parts(&audio.instruments[0], 4);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL2])
            {
                instrument_set_parts(&audio.instruments[1], 4);
            }
            break;

        case KEY_FIVE_PART:

            if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
            {
                instrument_set_parts(&audio.instruments[0], 5);
                instrument_set_parts(&audio.instruments[1], 5);

            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL1])
            {
                instrument_set_parts(&audio.instruments[0], 5);
            }
            if (input.pressed_keys[KEY_SELECT_CHANNEL2])
            {
                instrument_set_parts(&audio.instruments[1], 5);
            }
            break;
        case KEY_NOTE_LEFT_1:
            instrument_play(&audio.instruments[0], 0);
            break;
        case KEY_NOTE_LEFT_2:
            instrument_play(&audio.instruments[0], 1);
            break;
        case KEY_NOTE_LEFT_3:
            instrument_play(&audio.instruments[0], 2);
            break;
        case KEY_NOTE_LEFT_4:
            instrument_play(&audio.instruments[0], 3);
            break;
        case KEY_NOTE_LEFT_5:
            instrument_play(&audio.instruments[0], 4);
            break;
        case KEY_NOTE_LEFT_6:
            instrument_play(&audio.instruments[0], 5);
            break;
        case KEY_NOTE_LEFT_7:
            instrument_play(&audio.instruments[0], 6);
            break;
        case KEY_NOTE_LEFT_8:
            instrument_play(&audio.instruments[0], 7);
            break;
        case KEY_NOTE_LEFT_9:
            instrument_play(&audio.instruments[0], 8);
            break;
        case KEY_NOTE_LEFT_10:
            instrument_play(&audio.instruments[0], 9);
            break;
        case KEY_NOTE_LEFT_11:
            instrument_play(&audio.instruments[0], 10);
            break;
        case KEY_NOTE_LEFT_12:
            instrument_play(&audio.instruments[0], 11);
            break;
        case KEY_NOTE_LEFT_13:
            instrument_play(&audio.instruments[0], 12);
            break;
        case KEY_NOTE_LEFT_14:
            instrument_play(&audio.instruments[0], 13);
            break;
        case KEY_NOTE_LEFT_15:
            instrument_play(&audio.instruments[0], 14);
            break;
        case KEY_SELECT_CHANNEL1:
            for (int i = 0 ; i < NUMBER_INSTRUMENTS ; i++)
            {
                for (int j = 0; j < MAX_SOUND_SHAPES_PER_INSTRUMENT; ++j)
                {
                    if (box_contain_vec2i(&program.sound_drawing_buttons[j + (i * MAX_SOUND_SHAPES_PER_INSTRUMENT)], &input.mouse_position))
                    {
                        printf("Selected button %d of instrument %d\n", j, i);
                        audio.instruments[i].current_sound_shape = audio.instruments[i].sound_shape[j];
                    }
                }
            }
            break;
        case SOUND_SHAPE_SELECTOR_1:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[0];
            break;
        case SOUND_SHAPE_SELECTOR_2:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[1];
            break;
        case SOUND_SHAPE_SELECTOR_3:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[2];
            break;
        case SOUND_SHAPE_SELECTOR_4:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[3];
            break;
        case SOUND_SHAPE_SELECTOR_5:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[4];
            break;
        case SOUND_SHAPE_SELECTOR_6:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[5];
            break;
        case SOUND_SHAPE_SELECTOR_7:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[6];
            break;
        case SOUND_SHAPE_SELECTOR_8:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[7];
            break;
        case SOUND_SHAPE_SELECTOR_9:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[8];
            break;
        case SOUND_SHAPE_SELECTOR_10:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[9];
            break;
        case SOUND_SHAPE_SELECTOR_11:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[10];
            break;
        case SOUND_SHAPE_SELECTOR_12:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[11];
            break;
        case SOUND_SHAPE_SELECTOR_13:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[12];
            break;
        case SOUND_SHAPE_SELECTOR_14:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[13];
            break;
        case SOUND_SHAPE_SELECTOR_15:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[14];
            break;
        case SOUND_SHAPE_SELECTOR_16:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[15];
            break;
        case SOUND_SHAPE_SELECTOR_17:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[16];
            break;
        case SOUND_SHAPE_SELECTOR_18:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[17];
            break;
        case SOUND_SHAPE_SELECTOR_19:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[18];
            break;
        case SOUND_SHAPE_SELECTOR_20:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[19];
            break;
        case SOUND_SHAPE_SELECTOR_21:
            audio.instruments[0].current_sound_shape = audio.instruments[0].sound_shape[20];
            break;

    }
    logging_trace("key down");
}

void
key_up(enum key key)
{
    input.pressed_keys[key] = false;
    switch (key)
    {
        case KEY_NOTE_LEFT_1:
            instrument_release_note(&audio.instruments[0], 0);
            break;
        case KEY_NOTE_LEFT_2:
            instrument_release_note(&audio.instruments[0], 1);
            break;
        case KEY_NOTE_LEFT_3:
            instrument_release_note(&audio.instruments[0], 2);
            break;
        case KEY_NOTE_LEFT_4:
            instrument_release_note(&audio.instruments[0], 3);
            break;
        case KEY_NOTE_LEFT_5:
            instrument_release_note(&audio.instruments[0], 4);
            break;
        case KEY_NOTE_LEFT_6:
            instrument_release_note(&audio.instruments[0], 5);
            break;
        case KEY_NOTE_LEFT_7:
            instrument_release_note(&audio.instruments[0], 6);
            break;
        case KEY_NOTE_LEFT_8:
            instrument_release_note(&audio.instruments[0], 7);
            break;
        case KEY_NOTE_LEFT_9:
            instrument_release_note(&audio.instruments[0], 8);
            break;
        case KEY_NOTE_LEFT_10:
            instrument_release_note(&audio.instruments[0], 9);
            break;
        case KEY_NOTE_LEFT_11:
            instrument_release_note(&audio.instruments[0], 10);
            break;
        case KEY_NOTE_LEFT_12:
            instrument_release_note(&audio.instruments[0], 11);
            break;
        case KEY_NOTE_LEFT_13:
            instrument_release_note(&audio.instruments[0], 12);
            break;
        case KEY_NOTE_LEFT_14:
            instrument_release_note(&audio.instruments[0], 13);
            break;
        case KEY_NOTE_LEFT_15:
            instrument_release_note(&audio.instruments[0], 14);
            break;
        case KEY_SELECT_CHANNEL1:
            input.is_drawing = false;
            break;
    }
}

void
draw_in_canvas(struct sound_drawing_canvas *canvas)
{
    input.is_drawing = true;
    struct vec2i position_in_canvas;
    position_in_canvas.x = input.mouse_position.x - canvas->box.left;
    position_in_canvas.y = input.mouse_position.y - canvas->box.bottom;

    for (int i = -11; i < 11; ++i)
    {
        int x = position_in_canvas.x - i;
        if (x < 0 || x >= DRAW_SPACE_WIDTH)
        {
            continue;
        }
        canvas->instrument->current_sound_shape[x] = position_in_canvas.y;
    }
}

void
key_pressing()
{
    if (!input.is_drawing &&
        box_contain_vec2i(&program.playing_area_box, &input.mouse_position))
    {
        if (input.pressed_keys[KEY_SELECT_CHANNEL1_AND_2])
        {
            program.pointers[0].x += input.mouse_delta.x;
            program.pointers[0].y += input.mouse_delta.y;
            program.pointers[1].x += input.mouse_delta.x;
            program.pointers[1].y += input.mouse_delta.y;
            audio_init_note_frequencies_and_volume();
        }
        else if (input.pressed_keys[KEY_SELECT_CHANNEL1])
        {
            program.pointers[0] = input.mouse_position;
            audio_init_note_frequencies_and_volume();
        }
        else if (input.pressed_keys[KEY_SELECT_CHANNEL2])
        {
            program.pointers[1] = input.mouse_position;
            audio_init_note_frequencies_and_volume();
        }
    }
    else
    {
        if (input.pressed_keys[KEY_SELECT_CHANNEL1])
        {
            for (int i = 0; i < 2; ++i)
            {
                if (box_contain_vec2i(
                        &program.sound_drawing_canvas[i].box
                        , &input.mouse_position
                ))
                {
                    draw_in_canvas(&program.sound_drawing_canvas[i]);
                }
            }
        }
    }

}

void
mouse_move(SDL_MouseMotionEvent e)
{
    input.mouse_position.x = e.x;
    input.mouse_position.y = renderer.window_size.y - e.y;
    input.mouse_delta.x = e.xrel;
    input.mouse_delta.y = -e.yrel;
}

void
input_init_move_multiplier() {
    input.move_right_multiplier = 0;
    input.move_left_multiplier = 0;
}

void
input_poll()
{
    unsigned int current_time = SDL_GetTicks();
    for (int i = 0; i < KEY_ALL; i++)
    {
        input.previous_pressed_keys[i] = input.pressed_keys[i];
    }
    input.mouse_delta.x = 0;
    input.mouse_delta.y = 0;

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
            case SDL_QUIT:
                program.quit = true;
                break;
            case SDL_KEYDOWN:
                key_down(key_mapping[e.key.keysym.scancode]);
                break;
            case SDL_KEYUP:
                key_up(key_mapping[e.key.keysym.scancode]);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button >= MAX_MOUSE_BUTTONS)
                {
                    continue;
                }

                logging_trace("%d\n", e.button.button);
                key_down(mouse_mapping[e.button.button]);
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button >= MAX_MOUSE_BUTTONS)
                {
                    continue;
                }
                key_up(mouse_mapping[e.button.button]);
                break;
            case SDL_MOUSEMOTION:
                mouse_move(e.motion);
                break;
            case SDL_MOUSEWHEEL:
                if (input.pressed_keys[KEY_SELECT_CHANNEL1])
                {
                    instrument_move_left(
                            &audio.instruments[0], 0.01 * e.wheel.y * input.move_left_multiplier
                    );

                    input.move_left_multiplier = 1 / ((current_time - input.last_move_left) / 1000.0);
                    input.last_move_left = current_time;
                }
                else if (input.pressed_keys[KEY_SELECT_CHANNEL2])
                {
                    instrument_move_right(
                            &audio.instruments[1], 0.01 * e.wheel.y * input.move_right_multiplier
                    );
                    input.move_left_multiplier = 1 / ((current_time - input.last_move_right) / 1000.0);
                    input.last_move_right = current_time;
                }
                if (input.move_right_multiplier > 5) {
                    input.move_right_multiplier = 5;
                }
                if (input.move_left_multiplier > 5) {
                    input.move_left_multiplier = 5;
                }
                if (input.move_right_multiplier < 1) {
                    input.move_right_multiplier = 1;
                }
                if (input.move_left_multiplier < 1) {
                    input.move_left_multiplier = 1;
                }
            default:
                break;
        }
    }

    key_pressing();

    if (input.pressed_keys[KEY_EXIT])
    {
        program.quit = true;
    }
}

