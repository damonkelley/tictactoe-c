#include "board.h"
#include <criterion/criterion.h>

Test(Board, APieceCanBeAdded) {
    Board *board = board_new();
    board->add(board, 'X', 1);

    char expected[] = {'\0', 'X', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};

    for (int i = 0; i < 9; i++) {
        if (board->spaces[i] != expected[i])
            cr_assert_fail("INDEX %d: %d does not equal %d", i,
                           board->spaces[i], expected[i]);
    }

    board->destroy(board);
}

Test(Board, AnErrorIsReturnedIfThePeicesCannotBeAdded) {
    Board *board = board_new();

    int err = board->add(board, 'X', 11);
    cr_assert_eq(err, 1);

    err = board->add(board, 'O', -1);
    cr_assert_eq(err, 1);

    board->destroy(board);
}
