#include "loop.h"
#include <criterion/criterion.h>
#include "board.h"
#include "game.h"
#include "ui.h"

typedef int (*Reader)(void);

static int x_wins() {
    static int moves[5] = {0, 3, 1, 4, 2};
    static int* move = moves;
    return *move++;
}

static int draw() {
    static int moves[9] = {0, 2, 6, 3, 4, 8, 5, 1, 7};
    static int* move = moves;
    return *move++;
}

static void __write() {}

static UI fake_ui(Reader reader) {
    UI ui;
    ui.read = reader;
    ui.write = __write;
    return ui;
}

Test(Loop, ItStopsWhenTheGameHasAWinner) {
    Board* board = BoardNew();
    Game* game = GameNew(board);

    UI ui = fake_ui(x_wins);

    loop(game, &ui);
    cr_assert_eq(game->outcome, Winner);
    cr_assert_eq(game->winner, 'X');
}

Test(Loop, ItStopsWhenTheGameIsOver) {
    Board* board = BoardNew();
    Game* game = GameNew(board);

    UI ui = fake_ui(draw);

    loop(game, &ui);
    cr_assert_eq(game->outcome, Draw);
    cr_assert_eq(game->winner, false);
}
