#include <SDL2/SDL_events.h>
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
    key_mapping[SDL_SCANCODE_Y] = KEY_NOTE_RIGHT_1;
    key_mapping[SDL_SCANCODE_U] = KEY_NOTE_RIGHT_2;
    key_mapping[SDL_SCANCODE_I] = KEY_NOTE_RIGHT_3;
    key_mapping[SDL_SCANCODE_O] = KEY_NOTE_RIGHT_4;
    key_mapping[SDL_SCANCODE_P] = KEY_NOTE_RIGHT_5;
    key_mapping[SDL_SCANCODE_H] = KEY_NOTE_RIGHT_6;
    key_mapping[SDL_SCANCODE_J] = KEY_NOTE_RIGHT_7;
    key_mapping[SDL_SCANCODE_K] = KEY_NOTE_RIGHT_8;
    key_mapping[SDL_SCANCODE_L] = KEY_NOTE_RIGHT_9;
    key_mapping[SDL_SCANCODE_SEMICOLON] = KEY_NOTE_RIGHT_10;
    key_mapping[SDL_SCANCODE_N] = KEY_NOTE_RIGHT_11;
    key_mapping[SDL_SCANCODE_M] = KEY_NOTE_RIGHT_12;
    key_mapping[SDL_SCANCODE_COMMA] = KEY_NOTE_RIGHT_13;
    key_mapping[SDL_SCANCODE_PERIOD] = KEY_NOTE_RIGHT_14;
    key_mapping[SDL_SCANCODE_SLASH] = KEY_NOTE_RIGHT_15;
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
        case KEY_NOTE_RIGHT_1:
            instrument_play(&audio.instruments[1], 0);
            break;
        case KEY_NOTE_RIGHT_2:
            instrument_play(&audio.instruments[1], 1);
            break;
        case KEY_NOTE_RIGHT_3:
            instrument_play(&audio.instruments[1], 2);
            break;
        case KEY_NOTE_RIGHT_4:
            instrument_play(&audio.instruments[1], 3);
            break;
        case KEY_NOTE_RIGHT_5:
            instrument_play(&audio.instruments[1], 5);
            break;
        case KEY_NOTE_RIGHT_6:
            instrument_play(&audio.instruments[1], 5);
            break;
        case KEY_NOTE_RIGHT_7:
            instrument_play(&audio.instruments[1], 6);
            break;
        case KEY_NOTE_RIGHT_8:
            instrument_play(&audio.instruments[1], 7);
            break;
        case KEY_NOTE_RIGHT_9:
            instrument_play(&audio.instruments[1], 8);
            break;
        case KEY_NOTE_RIGHT_10:
            instrument_play(&audio.instruments[1], 9);
            break;
        case KEY_NOTE_RIGHT_11:
            instrument_play(&audio.instruments[1], 10);
            break;
        case KEY_NOTE_RIGHT_12:
            instrument_play(&audio.instruments[1], 11);
            break;
        case KEY_NOTE_RIGHT_13:
            instrument_play(&audio.instruments[1], 12);
            break;
        case KEY_NOTE_RIGHT_14:
            instrument_play(&audio.instruments[1], 13);
            break;
        case KEY_NOTE_RIGHT_15:
            instrument_play(&audio.instruments[1], 14);
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
        case KEY_NOTE_RIGHT_1:
            instrument_release_note(&audio.instruments[1], 0);
            break;
        case KEY_NOTE_RIGHT_2:
            instrument_release_note(&audio.instruments[1], 1);
            break;
        case KEY_NOTE_RIGHT_3:
            instrument_release_note(&audio.instruments[1], 2);
            break;
        case KEY_NOTE_RIGHT_4:
            instrument_release_note(&audio.instruments[1], 3);
            break;
        case KEY_NOTE_RIGHT_5:
            instrument_release_note(&audio.instruments[1], 5);
            break;
        case KEY_NOTE_RIGHT_6:
            instrument_release_note(&audio.instruments[1], 5);
            break;
        case KEY_NOTE_RIGHT_7:
            instrument_release_note(&audio.instruments[1], 6);
            break;
        case KEY_NOTE_RIGHT_8:
            instrument_release_note(&audio.instruments[1], 7);
            break;
        case KEY_NOTE_RIGHT_9:
            instrument_release_note(&audio.instruments[1], 8);
            break;
        case KEY_NOTE_RIGHT_10:
            instrument_release_note(&audio.instruments[1], 9);
            break;
        case KEY_NOTE_RIGHT_11:
            instrument_release_note(&audio.instruments[1], 10);
            break;
        case KEY_NOTE_RIGHT_12:
            instrument_release_note(&audio.instruments[1], 11);
            break;
        case KEY_NOTE_RIGHT_13:
            instrument_release_note(&audio.instruments[1], 12);
            break;
        case KEY_NOTE_RIGHT_14:
            instrument_release_note(&audio.instruments[1], 13);
            break;
        case KEY_NOTE_RIGHT_15:
            instrument_release_note(&audio.instruments[1], 14);
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
input_poll()
{
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
                            &audio.instruments[0], 0.01 * e.wheel.y
                    );
                }
                else if (input.pressed_keys[KEY_SELECT_CHANNEL2])
                {
                    instrument_move_right(
                            &audio.instruments[1], 0.01 * e.wheel.y
                    );
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

