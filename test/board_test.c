#include "board.h"
#include <criterion/criterion.h>

static Board *board;

static void setup(void) { board = BoardNew(); }

static void teardown(void) { board->destroy(board); }

Test(Board, APieceCanBeAdded, .init = setup, .fini = teardown) {
    board->add(board, 'X', 1);

    Space expected[] = {EMPTY_SPACE, 'X',         EMPTY_SPACE,
                        EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE,
                        EMPTY_SPACE, EMPTY_SPACE, EMPTY_SPACE};

    for (int i = 0; i < board->size; i++) {
        if (board->spaces[i] != expected[i])
            cr_assert_fail("INDEX %d: %d does not equal %d", i,
                           board->spaces[i], expected[i]);
    }
}

Test(Board, FalseIsReturnedIfThePeicesCannotBeAdded, .init = setup,
     .fini = teardown) {
    bool result = board->add(board, 'X', 11);
    cr_assert_eq(result, false);

    result = board->add(board, 'O', -1);
    cr_assert_eq(result, false);
}

Test(Board, ASpaceCanBeQueried, .init = setup, .fini = teardown) {
    Space space = board->get(board, 1);
    cr_assert_eq(space, EMPTY_SPACE);

    board->add(board, 'O', 1);
    space = board->get(board, 1);

    cr_assert_eq(space, 'O');
}

Test(Board, ItReturnsFalseWhenTheIndexDoesntExists, .init = setup,
     .fini = teardown) {
    Space space = board->get(board, 11);
    cr_assert_eq(space, false);

    space = board->get(board, -1);
    cr_assert_eq(space, false);
}

Test(Board, ItHasAvailableAndUnavailableSpaces, .init = setup,
     .fini = teardown) {
    board->add(board, 'X', 1);

    cr_assert_eq(board->is_available(board, 0), 1);
    cr_assert_eq(board->is_available(board, 1), 0);
    cr_assert_eq(board->is_available(board, -1), 0);
}
