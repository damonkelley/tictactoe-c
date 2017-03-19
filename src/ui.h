#ifndef __UI_H
#define __UI_H
#include <stdio.h>

typedef struct UI {
    FILE *out;
    FILE *in;
    int (*read_move)(struct UI *self);
    void (*update)(struct UI *self);
    void (*display)(struct UI *self, char *message);
    void (*destroy)(struct UI *self);
} UI;

UI *UINew(FILE *in, FILE *out);

#endif
