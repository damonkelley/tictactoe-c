#include "board.h"

typedef struct Game {
    void (*move)(struct Game *self, int space);
    void (*destroy)(struct Game *self);
    char next_player;
    Board *board;
} Game;

Game *GameNew(Board *board);
