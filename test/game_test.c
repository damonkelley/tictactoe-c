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

Test(Game, APlayerCanMove) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    game->move(game, 1);

    cr_assert_eq(board->get(board, 1), 'X');

    game->destroy(game);
}

Test(Game, ItAlternatesThePlayers) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    game->move(game, 1);
    game->move(game, 0);
    game->move(game, 3);

    cr_assert_eq(board->get(board, 1), 'X');
    cr_assert_eq(board->get(board, 0), 'O');
    cr_assert_eq(board->get(board, 3), 'X');

    game->destroy(game);
}

Test(Game, ItPreventsAMoveToAnOccupiedSpace) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    bool result = game->move(game, 1);
    cr_assert_eq(result, true);
    cr_assert_eq(board->get(board, 1), 'X');

    result = game->move(game, 1);
    cr_assert_eq(result, false);
    cr_assert_eq(board->get(board, 1), 'X');

    game->destroy(game);
}

Test(Game, TheOutcomeIsInProgress) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    cr_assert_eq(game->outcome, InProgress);

    game->move(game, 0);
    cr_assert_eq(game->outcome, InProgress);
}

Test(Game, TheOutcomeIsWinner) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    make_win(game);

    cr_assert_eq(game->outcome, Winner);
}

Test(Game, TheOutcomeIsDraw) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    make_draw(game);

    cr_assert_eq(game->outcome, Draw);
}

Test(Game, ItHasAWinner) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    cr_assert_eq(game->winner, false);

    make_win(game);

    cr_assert_eq(game->winner, 'X');
}

Test(Game, ThereIsNoWinnerWhenTheGameIsADraw) {
    Board *board = BoardNew();
    Game *game = GameNew(board);

    make_draw(game);

    cr_assert_eq(game->winner, false);
}
