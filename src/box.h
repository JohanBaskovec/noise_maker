#ifndef NOISE_MAKER_BOX_H
#define NOISE_MAKER_BOX_H
#include "stdbool.h"
#include "vec.h"

struct box {
    int left;
    int top;
    int right;
    int bottom;
    int width;
    int height;
};

bool
box_contain_vec2i(struct box *box, struct vec2i *vec2i);

void
box_init_from_position_and_size(struct box *box, int left, int top, int width, int height);

void
box_set_width(struct box *box, int width);

void
box_set_height(struct box *box, int height);
#endif //NOISE_MAKER_BOX_H
