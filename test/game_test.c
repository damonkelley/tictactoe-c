#include "game.h"
#include <criterion/criterion.h>

void make_win(Game *game) {
    game->move(game, 0);
    game->move(game, 3);
    game->move(game, 1);
    game->move(game, 4);
    game->move(game, 2);
}

void make_draw(Game *game) {
    game->move(game, 0);
    game->move(game, 2);
    game->move(game, 6);
    game->move(game, 3);
    game->move(game, 4);
    game->move(game, 8);
    game->move(game, 5);
    game->move(game, 1);
    game->move(game, 7);
}

Board *board;
Game *game;

static void setup(void) {
    board = BoardNew();
    game = GameNew(board);
}

static void teardown(void) { game->destroy(game); }

Test(Game, APlayerCanMove, .init = setup, .fini = teardown) {
    game->move(game, 1);
    cr_assert_eq(board->get(board, 1), 'X');
}

Test(Game, ItAlternatesThePlayers, .init = setup, .fini = teardown) {
    game->move(game, 1);
    game->move(game, 0);
    game->move(game, 3);

    cr_assert_eq(board->get(board, 1), 'X');
    cr_assert_eq(board->get(board, 0), 'O');
    cr_assert_eq(board->get(board, 3), 'X');
}

Test(Game, ItPreventsAMoveToAnOccupiedSpace, .init = setup, .fini = teardown) {
    bool result = game->move(game, 1);
    cr_assert_eq(result, true);
    cr_assert_eq(board->get(board, 1), 'X');

    result = game->move(game, 1);
    cr_assert_eq(result, false);
    cr_assert_eq(board->get(board, 1), 'X');
}

Test(Game, TheOutcomeIsInProgress, .init = setup, .fini = teardown) {
    cr_assert_eq(game->outcome, InProgress);

    game->move(game, 0);

    cr_assert_eq(game->outcome, InProgress);
}

Test(Game, TheOutcomeIsWinner, .init = setup, .fini = teardown) {
    make_win(game);
    cr_assert_eq(game->outcome, Winner);
}

Test(Game, TheOutcomeIsDraw, .init = setup, .fini = teardown) {
    make_draw(game);
    cr_assert_eq(game->outcome, Draw);
}

Test(Game, ItHasAWinner, .init = setup, .fini = teardown) {
    cr_assert_eq(game->winner, false);

    make_win(game);

    cr_assert_eq(game->winner, 'X');
}

Test(Game, ThereIsNoWinnerWhenTheGameIsADraw, .init = setup, .fini = teardown) {
    make_draw(game);
    cr_assert_eq(game->winner, false);
}
