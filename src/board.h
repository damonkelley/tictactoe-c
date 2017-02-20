#define EMPTY_SPACE '-'

#include <stdbool.h>

typedef char Space;

typedef struct Board {
    Space spaces[9];
    int (*add)(struct Board *self, char marker, int id);
    Space (*get)(struct Board *self, int id);
    void (*destroy)(struct Board *self);
    bool (*is_available)(struct Board *self, int id);
} Board;

Board *BoardNew();
