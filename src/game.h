#ifndef __GAME_H
#define __GAME_H

#include <stdbool.h>
#include "board.h"

typedef enum { InProgress, Winner, Draw } Outcome;

typedef struct Game {
    bool (*move)(struct Game *self, int space);
    void (*destroy)(struct Game *self);
    char turn;
    char winner;
    Outcome outcome;
    Board *board;
} Game;

Game *GameNew(Board *board);
#endif
