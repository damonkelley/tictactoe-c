#include "presenter.h"
#include <criterion/criterion.h>

Test(Presenter, ItPresentsANewGame) {
    Game *game = GameNew(BoardNew());
    char *output = present(game);

    char *expected =
        " 1 | 2 | 3\n"
        "---+---+---\n"
        " 4 | 5 | 6\n"
        "---+---+---\n"
        " 7 | 8 | 9\n";

    cr_assert_str_eq(output, expected);
}

Test(Presenter, ItPresentsAGameWithOneMove) {
    Game *game = GameNew(BoardNew());

    game->move(game, 5);

    char *output = present(game);

    char *expected =
        " 1 | 2 | 3\n"
        "---+---+---\n"
        " 4 | X | 6\n"
        "---+---+---\n"
        " 7 | 8 | 9\n";

    cr_assert_str_eq(output, expected);
}
