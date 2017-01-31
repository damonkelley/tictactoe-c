#include "game.h"
#include <stdlib.h>

static void alternate_player(Game* self) {
    self->next_player = self->next_player == 'X' ? 'O' : 'X';
}

static bool Game_move(Game* self, int space) {
    if (!self->board->is_available(self->board, space)) return false;

    self->board->add(self->board, self->next_player, space);
    alternate_player(self);
    return true;
}

static void Game_destroy(Game* self) {
    self->board->destroy(self->board);
    free(self);
}

Game* GameNew(Board* board) {
    Game* game = malloc(sizeof(Game));
    game->board = board;
    game->move = Game_move;
    game->destroy = Game_destroy;
    game->next_player = 'X';
    return game;
}
