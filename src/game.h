#include <stdbool.h>
#include "board.h"

typedef enum { InProgress, Winner, Draw } Outcome;

typedef struct Game {
    bool (*move)(struct Game *self, int space);
    void (*destroy)(struct Game *self);
    char next_player;
    Outcome outcome;
    Board *board;
} Game;

Game *GameNew(Board *board);
