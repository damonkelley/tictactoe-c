#include "board.h"
#include <stdlib.h>
#include <string.h>

static int Board_add(Board *self, char marker, int space) {
    if (space > 9 || space < 0) return -1;

    self->spaces[space] = marker;
    return 0;
}

static char Board_get(Board *self, int space) {
    if (space > 9 || space < 0) return -1;
    return self->spaces[space];
}


static void Board_destroy(Board *self) { free(self); }

Board *BoardNew() {
    char spaces[9] = {'\0'};

    Board *board = malloc(sizeof(Board));
    memcpy(board->spaces, spaces, sizeof(board->spaces));
    board->add = Board_add;
    board->get = Board_get;
    board->destroy = Board_destroy;

    return board;
}
