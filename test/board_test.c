#include "board.h"
#include <criterion/criterion.h>

Test(Board, APieceCanBeAdded) {
    Board *board = BoardNew();
    board->add(board, 'X', 1);

    Space expected[] = {EMPTY_SPACE, 'X',         EMPTY_SPACE,
                       EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE,
                       EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE};

    for (int i = 0; i < 9; i++) {
        if (board->spaces[i] != expected[i])
            cr_assert_fail("INDEX %d: %d does not equal %d", i,
                           board->spaces[i], expected[i]);
    }

    board->destroy(board);
}

Test(Board, FalseIsReturnedIfThePeicesCannotBeAdded) {
    Board *board = BoardNew();

    bool result = board->add(board, 'X', 11);
    cr_assert_eq(result, false);

    result = board->add(board, 'O', -1);
    cr_assert_eq(result, false);

    board->destroy(board);
}

Test(Board, ASpaceCanBeQueried) {
    Board *board = BoardNew();

    Space space = board->get(board, 1);
    cr_assert_eq(space, EMPTY_SPACE);

    board->add(board, 'O', 1);
    space = board->get(board, 1);

    cr_assert_eq(space, 'O');

    board->destroy(board);
}

Test(Board, ItReturnsFalseWhenTheIndexDoesntExists) {
    Board *board = BoardNew();

    Space space = board->get(board, 11);
    cr_assert_eq(space, false);

    space = board->get(board, -1);
    cr_assert_eq(space, false);

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
