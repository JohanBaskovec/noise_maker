#include "box.h"

bool
box_contain_vec2i(struct box *box, struct vec2i *vec2i)
{
    return vec2i->x >= box->left && vec2i->x <= box->right &&
           vec2i->y >= box->bottom && vec2i->y <= box->top;
}

void
box_set_width(struct box *box, int width)
{
    box->width = width;
    box->right = box->left + width;
}

void
box_set_height(struct box *box, int height)
{
    box->height = height;
    box->top = box->bottom + height;
}