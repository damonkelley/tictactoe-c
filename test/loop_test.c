#include "loop.h"
#include <criterion/criterion.h>
#include "board.h"
#include "game.h"
#include "ui.h"

#define UNUSED(x) (void)(x)

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

static char* buffer;
static size_t len;

static void writer(UI* self, char* message) {
    UNUSED(message);
    fputs("turn ", self->out);
    fflush(self->out);
}

extern FILE* open_memstream(char** ptr, size_t* sizeloc);

static void fake_ui(UI* ui, Reader reader) {
    ui->read = reader;
    ui->write = writer;
    ui->out = open_memstream(&buffer, &len);
}

static Game* game;
static Board* board;
static UI ui;

static void setup(void) {
    board = BoardNew();
    game = GameNew(board);
}

static void teardown(void) { game->destroy(game); }

Test(Loop, ItStopsWhenTheGameHasAWinner, .init = setup, .fini = teardown) {
    fake_ui(&ui, x_wins);

    loop(game, &ui);

    cr_assert_eq(game->outcome, Winner);
    cr_assert_eq(game->winner, 'X');
}

Test(Loop, ItStopsWhenTheGameIsOver, .init = setup, .fini = teardown) {
    fake_ui(&ui, draw);

    loop(game, &ui);
    cr_assert_eq(game->outcome, Draw);
    cr_assert_eq(game->winner, false);
}

Test(Loop, ItPrintsAMessageOnEveryLoop, .init = setup, .fini = teardown) {
    fake_ui(&ui, x_wins);

    loop(game, &ui);

    cr_assert_str_eq("turn turn turn turn turn ", buffer);
}
