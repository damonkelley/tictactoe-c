#include "game.h"
#include <criterion/criterion.h>

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
