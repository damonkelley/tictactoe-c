#include "game.h"
#include <stdlib.h>

static bool can_move(Game* self, int space) {
    return self->board->is_available(self->board, space);
}

static char get(Game* self, int space) {
    return self->board->get(self->board, space);
}

static bool all_markers_match(Game* self, int spaces[3]) {
    char a = get(self, spaces[0]);
    char b = get(self, spaces[1]);
    char c = get(self, spaces[2]);

    if (a != EMPTY_SPACE) {
        return a == b && a == c;
    } else {
        return false;
    }
}

int WINS[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6},
    {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6},
};

static bool has_winner(Game* self) {
    for (int i = 0; i < 8; i++) {
        if (all_markers_match(self, WINS[i])) return true;
    }
    return false;
}

static bool is_draw(Game* self) {
    for (int space = 0; space < 8; space++) {
        if (can_move(self, space)) return false;
    }
    return true;
}

static void update_outcome(Game* self) {
    if (has_winner(self))
        self->outcome = Winner;
    else if (is_draw(self))
        self->outcome = Draw;
}

static void update_winner(Game* self) {
    if (has_winner(self)) self->winner = self->turn;
}

static void update_turn(Game* self) {
    self->turn = self->turn == 'X' ? 'O' : 'X';
}

static void update_game(Game* self) {
    update_outcome(self);
    update_winner(self);
    update_turn(self);
}

static bool move(Game* self, int space) {
    if (!can_move(self, space)) {
        return false;
    }

    Board* board = self->board;
    board->add(board, self->turn, space);

    update_game(self);
    return true;
}

static void destroy(Game* self) {
    self->board->destroy(self->board);
    free(self);
}

Game* GameNew(Board* board) {
    Game* game = malloc(sizeof(Game));
    game->board = board;
    game->move = move;
    game->destroy = destroy;
    game->turn = 'X';
    game->winner = false;
    game->outcome = InProgress;
    return game;
}
