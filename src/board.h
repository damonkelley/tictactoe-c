#ifndef __BOARD_H
#define __BOARD_H

#define EMPTY_SPACE '-'

#include <stdbool.h>

typedef char Marker;

typedef struct Space {
    struct Space *next;
    int id;
    Marker value;
} Space;

#define FOREACH_SPACE(SPACE, SPACES) \
    for (Space * (SPACE) = (SPACES); (SPACE) != NULL; (SPACE) = (SPACE)->next)

typedef struct Board {
    Space *spaces;
    int (*add)(struct Board *self, char marker, int id);
    char (*get)(struct Board *self, int id);
    void (*destroy)(struct Board *self);
    bool (*is_available)(struct Board *self, int id);
    int size;
} Board;

Board *BoardNew();
#endif
