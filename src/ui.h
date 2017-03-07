#ifndef __UI_H
#define __UI_H
#include <stdio.h>

typedef struct UI {
    FILE * out;
    int (*read)(void);
    void (*write)(struct UI *self, char *message);
} UI;

#endif
