#include "loop.h"
#include <criterion/criterion.h>
#include <string.h>
#include "board.h"
#include "game.h"
#include "ui.h"

#define UNUSED(x) (void)(x)

extern FILE* open_memstream(char** ptr, size_t* sizeloc);
extern FILE* fmemopen(void* buf, size_t size, const char* mode);

static char* buffer;
static size_t len;

static UI* FakeUI(char* moves) {
    FILE* out = open_memstream(&buffer, &len);
    FILE* in = fmemopen(moves, strlen(moves), "r");
    return UINew(in, out);
}

static char* fake_presenter(Game* game) {
    UNUSED(game);
    return "turn ";
}

static Game* game;
static UI* ui;

static void setup(void) {
    Board* board = BoardNew();
    game = GameNew(board);
}

static void teardown(void) {
    game->destroy(game);
    ui->destroy(ui);
}

Test(Loop, ItStopsWhenTheGameHasAWinner, .init = setup, .fini = teardown,
     .timeout = 1.0) {
    ui = FakeUI("1 4 2 5 3");

    loop(game, ui, fake_presenter);

    cr_assert_eq(game->outcome, Winner);
    cr_assert_eq(game->winner, 'X');
}

Test(Loop, ItStopsWhenTheGameIsOver, .init = setup, .fini = teardown,
     .timeout = 1.0) {
    ui = FakeUI("1 3 7 4 5 9 6 2 8");

    loop(game, ui, fake_presenter);
    cr_assert_eq(game->outcome, Draw);
    cr_assert_eq(game->winner, false);
}

Test(Loop, ItPresentsTheGameOnEveryTurn, .init = setup, .fini = teardown,
     .timeout = 1.0) {
    ui = FakeUI("1 4 2 5 3");

    loop(game, ui, fake_presenter);

    cr_assert_str_eq("turn turn turn turn turn turn ", buffer);
}
