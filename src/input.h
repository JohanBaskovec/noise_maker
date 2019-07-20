

#ifndef NOISE_MAKER_INPUT_H
#define NOISE_MAKER_INPUT_H

#include <stdbool.h>
#include <vec.h>

#define NOTE_PER_SIDE 15

enum key {
    KEY_NOTE_LEFT_1,
    KEY_NOTE_LEFT_2,
    KEY_NOTE_LEFT_3,
    KEY_NOTE_LEFT_4,
    KEY_NOTE_LEFT_5,
    KEY_NOTE_LEFT_6,
    KEY_NOTE_LEFT_7,
    KEY_NOTE_LEFT_8,
    KEY_NOTE_LEFT_9,
    KEY_NOTE_LEFT_10,
    KEY_NOTE_LEFT_11,
    KEY_NOTE_LEFT_12,
    KEY_NOTE_LEFT_13,
    KEY_NOTE_LEFT_14,
    KEY_NOTE_LEFT_15,
    SOUND_SHAPE_SELECTOR_1,
    SOUND_SHAPE_SELECTOR_2,
    SOUND_SHAPE_SELECTOR_3,
    SOUND_SHAPE_SELECTOR_4,
    SOUND_SHAPE_SELECTOR_5,
    SOUND_SHAPE_SELECTOR_6,
    SOUND_SHAPE_SELECTOR_7,
    SOUND_SHAPE_SELECTOR_8,
    SOUND_SHAPE_SELECTOR_9,
    SOUND_SHAPE_SELECTOR_10,
    SOUND_SHAPE_SELECTOR_11,
    SOUND_SHAPE_SELECTOR_12,
    SOUND_SHAPE_SELECTOR_13,
    SOUND_SHAPE_SELECTOR_14,
    SOUND_SHAPE_SELECTOR_15,
    SOUND_SHAPE_SELECTOR_16,
    SOUND_SHAPE_SELECTOR_17,
    SOUND_SHAPE_SELECTOR_18,
    SOUND_SHAPE_SELECTOR_19,
    SOUND_SHAPE_SELECTOR_20,
    SOUND_SHAPE_SELECTOR_21,
    SOUND_SHAPE_SELECTOR_22,
    SOUND_SHAPE_SELECTOR_23,
    SOUND_SHAPE_SELECTOR_24,
    SOUND_SHAPE_SELECTOR_25,
    KEY_EXIT,
    KEY_SELECT_CHANNEL1,
    KEY_SELECT_CHANNEL2,
    KEY_SELECT_CHANNEL1_AND_2,
    KEY_ONE_PART,
    KEY_TWO_PART,
    KEY_THREE_PART,
    KEY_FOUR_PART,
    KEY_FIVE_PART,
    KEY_DRAW_MODE_0,

    KEY_DRAW_MODE_1,
    KEY_ALL,
    KEY_CHANGE_FREQUENCY_OFFSET,
    KEY_NONE
};

struct input {
    struct vec2i mouse_position;
    struct vec2i mouse_delta;
    double move_right_multiplier;
    double move_left_multiplier;
    unsigned int last_move_left;
    unsigned int last_move_right;
    bool pressed_keys[KEY_ALL];
    bool previous_pressed_keys[KEY_ALL];
    bool is_drawing;
};

extern struct input input;

void
input_poll();

void
input_init();

#endif //NOISE_MAKER_INPUT_H
