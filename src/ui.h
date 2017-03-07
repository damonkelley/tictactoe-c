#ifndef __UI_H
#define __UI_H
#include <stdio.h>

typedef struct UI {
    FILE * out;
    FILE * in;
    int (*read_move)(struct UI * self);
    void (*display)(struct UI *self, char *message);
} UI;

#endif
