

#ifndef NOISE_MAKER_INPUT_H
#define NOISE_MAKER_INPUT_H

#include <stdbool.h>

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
    KEY_NOTE_RIGHT_1,
    KEY_NOTE_RIGHT_2,
    KEY_NOTE_RIGHT_3,
    KEY_NOTE_RIGHT_4,
    KEY_NOTE_RIGHT_5,
    KEY_NOTE_RIGHT_6,
    KEY_NOTE_RIGHT_7,
    KEY_NOTE_RIGHT_8,
    KEY_NOTE_RIGHT_9,
    KEY_NOTE_RIGHT_10,
    KEY_NOTE_RIGHT_11,
    KEY_NOTE_RIGHT_12,
    KEY_NOTE_RIGHT_13,
    KEY_NOTE_RIGHT_14,
    KEY_NOTE_RIGHT_15,
    KEY_EXIT,
    KEY_SELECT_CHANNEL1,
    KEY_SELECT_CHANNEL2,
    KEY_SELECT_CHANNEL1_AND_2,
    KEY_ONE_PART,
    KEY_TWO_PART,
    KEY_THREE_PART,
    KEY_FOUR_PART,
    KEY_FIVE_PART,
    KEY_ALL,
    KEY_NONE
};

struct input {
    bool pressed_keys[KEY_ALL];
    bool previous_pressed_keys[KEY_ALL];
};

extern struct input input;

void
input_poll();

void
input_init();

#endif //NOISE_MAKER_INPUT_H
