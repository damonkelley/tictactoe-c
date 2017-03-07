#include "loop.h"
#include <criterion/criterion.h>
#include "board.h"
#include "game.h"
#include "ui.h"

#define UNUSED(x) (void)(x)

static void writer(UI* self, char* message) {
    UNUSED(message);
    fputs("turn ", self->out);
    fflush(self->out);
}

static int reader(UI* self) {
    int move;
    fscanf(self->in, "%d", &move);
    return move;
}

extern FILE* open_memstream(char** ptr, size_t* sizeloc);
extern FILE* fmemopen(void* buf, size_t size, const char* mode);

static char* buffer;
static size_t len;

static void FakeUI(UI* ui, char* moves) {
    ui->read_move = reader;
    ui->display = writer;

    ui->out = open_memstream(&buffer, &len);
    ui->in = fmemopen(moves, strlen(moves), "r");
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
    FakeUI(&ui, "0 3 1 4 2");

    loop(game, &ui);

    cr_assert_eq(game->outcome, Winner);
    cr_assert_eq(game->winner, 'X');
}

Test(Loop, ItStopsWhenTheGameIsOver, .init = setup, .fini = teardown) {
    FakeUI(&ui, "0 2 6 3 4 8 5 1 7");

    loop(game, &ui);
    cr_assert_eq(game->outcome, Draw);
    cr_assert_eq(game->winner, false);
}

Test(Loop, ItPrintsAMessageOnEveryLoop, .init = setup, .fini = teardown) {
    FakeUI(&ui, "0 3 1 4 2");

    loop(game, &ui);

    cr_assert_str_eq("turn turn turn turn turn ", buffer);
}
