#include "board.h"
#include <stdlib.h>
#include <string.h>

static bool is_valid(Board *board, int id) {
    return id > board->size || id < 0;
}

static int add(Board *board, char marker, int id) {
    if (is_valid(board, id)) return false;

    FOREACH_SPACE(space, board->spaces) {
        if (id == space->id) space->value = marker;
    }

    return true;
}

static char get(Board *board, int id) {
    if (is_valid(board, id)) return false;

    FOREACH_SPACE(space, board->spaces) {
        if (id == space->id) return space->value;
    }
    return false;
}

static bool is_available(Board *board, int space) {
    if (is_valid(board, space)) return false;
    return board->get(board, space) == EMPTY_SPACE;
}

static void destroy(Board *board) { free(board); }

static Space *SpaceNew(int id) {
    Space *space = malloc(sizeof(Space));
    space->value = EMPTY_SPACE;
    space->id = id;
    space->next = NULL;
    return space;
}

static Space *SpacesNew(int size) {
    Space *previous = NULL, *first = NULL;

    for (int id = 0; id < size; id++) {
        Space *space = SpaceNew(id);

        if (first == NULL) first = space;
        if (previous != NULL) previous->next = space;

        previous = space;
    }
    return first;
}

Board *BoardNew() {
    Board *board = malloc(sizeof(Board));
    board->spaces = SpacesNew(9);
    board->size = 9;
    board->add = add;
    board->get = get;
    board->is_available = is_available;
    board->destroy = destroy;

    return board;
}
