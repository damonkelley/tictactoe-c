#include "presenter.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "board.h"

static int id_to_char(int id) { return id + 49; }

static char format_space(Game* game, int space_id) {
    Board* board = game->board;
    char s;
    if ((s = board->get(board, space_id)) == EMPTY_SPACE)
        return id_to_char(space_id);
    else
        return s;
}

#define SEPARATOR "---+---+---\n"

char* present(Game* game) {
    static char buffer[12 * 5];

    Board* board = game->board;
    for (int i = 0; i < board->size; i++) {
        char space[3];
        if (i == 2 || i == 5) {
            sprintf(space, " %c\n", format_space(game, i));
            strcat(buffer, space);
            strcat(buffer, SEPARATOR);
        } else if (i == 8) {
            sprintf(space, " %c\n", format_space(game, i));
            strcat(buffer, space);
        } else {
            sprintf(space, " %c |", format_space(game, i));
            strcat(buffer, space);
        }
    }
    return buffer;
}
