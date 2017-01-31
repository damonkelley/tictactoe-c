#include "board.h"
#include <stdlib.h>
#include <string.h>

static bool is_valid(int space) { return space > 9 || space < 0; }

static int Board_add(Board *self, char marker, int space) {
    if (is_valid(space)) return -1;

    self->spaces[space] = marker;
    return 0;
}

static char Board_get(Board *self, int space) {
    if (is_valid(space)) return -1;
    return self->spaces[space];
}

static bool Board_is_available(Board *self, int space) {
    if (is_valid(space)) return 0;
    return self->get(self, space) == EMPTY_SPACE;
}

static void Board_destroy(Board *self) { free(self); }

Board *BoardNew() {
    char spaces[9] = {EMPTY_SPACE};

    Board *board = malloc(sizeof(Board));
    memcpy(board->spaces, spaces, sizeof(board->spaces));
    board->add = Board_add;
    board->get = Board_get;
    board->is_available = Board_is_available;
    board->destroy = Board_destroy;

    return board;
}
