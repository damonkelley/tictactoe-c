#include "presenter.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "board.h"

static int id_to_char(int id) { return id + 49; }

static char format_space(Game* game, int id) {
    Board* board = game->board;
    char s;
    if ((s = board->get(board, id)) == EMPTY_SPACE)
        return id_to_char(id);
    else
        return s;
}

#define SEPARATOR "---+---+---\n"

static void reset(char* buffer) { memset(&buffer[0], 0, sizeof(buffer)); }

char* present(Game* game) {
    static char buffer[12 * 5];
    reset(buffer);

    FOREACH_SPACE(space, game->board->spaces) {
        char cell[3];
        if (space->id == 2 || space->id == 5) {
            sprintf(cell, " %c\n", format_space(game, space->id));
            strcat(buffer, cell);
            strcat(buffer, SEPARATOR);
        } else if (space->id == 8) {
            sprintf(cell, " %c\n", format_space(game, space->id));
            strcat(buffer, cell);
        } else {
            sprintf(cell, " %c |", format_space(game, space->id));
            strcat(buffer, cell);
        }
    }
    return buffer;
}
