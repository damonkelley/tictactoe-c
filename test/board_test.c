#include "board.h"
#include <criterion/criterion.h>

Test(Board, APieceCanBeAdded) {
    Board *board = BoardNew();
    board->add(board, 'X', 1);

    char expected[] = {EMPTY_SPACE, 'X',         EMPTY_SPACE,
                       EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE,
                       EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE};

    for (int i = 0; i < 9; i++) {
        if (board->spaces[i] != expected[i])
            cr_assert_fail("INDEX %d: %d does not equal %d", i,
                           board->spaces[i], expected[i]);
    }

    board->destroy(board);
}

Test(Board, AnErrorIsReturnedIfThePeicesCannotBeAdded) {
    Board *board = BoardNew();

    int err = board->add(board, 'X', 11);
    cr_assert_eq(err, -1);

    err = board->add(board, 'O', -1);
    cr_assert_eq(err, -1);

    board->destroy(board);
}

Test(Board, ASpaceCanBeQueried) {
    Board *board = BoardNew();

    int marker = board->get(board, 1);
    cr_assert_eq(marker, 0);

    board->add(board, 'O', 1);
    marker = board->get(board, 1);

    cr_assert_eq(marker, 'O');

    board->destroy(board);
}

Test(Board, ItReturnsAnErrorWhenTheIndexDoesntExists) {
    Board *board = BoardNew();

    int err = board->get(board, 11);
    cr_assert_eq(err, -1);

    err = board->get(board, -1);
    cr_assert_eq(err, -1);

    board->destroy(board);
}

Test(Board, ItHasAvailableAndUnavailableSpaces) {
    Board *board = BoardNew();

    board->add(board, 'X', 1);

    cr_assert_eq(board->is_available(board, 0), 1);
    cr_assert_eq(board->is_available(board, 1), 0);
    cr_assert_eq(board->is_available(board, -1), 0);

    board->destroy(board);
}
