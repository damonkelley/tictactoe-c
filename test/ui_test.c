#include "ui.h"
#include <criterion/criterion.h>

extern FILE* open_memstream(char** ptr, size_t* sizeloc);
extern FILE* fmemopen(void* buf, size_t size, const char* mode);

static FILE* fake_out(char** buffer) {
    static size_t len;
    return open_memstream(buffer, &len);
}

static UI* ui;

static FILE* fake_in(char* input) {
    return fmemopen(input, strlen(input), "r");
}

static void teardown(void) { ui->destroy(ui); }

Test(UI, ItWillWriteToOut, .fini = teardown) {
    char* output;
    ui = UINew(fake_in(""), fake_out(&output));
    ui->display(ui, "foo");
    cr_assert_str_eq("foo", output);
}

Test(UI, ItWillReadAMove, .fini = teardown) {
    char* output;
    ui = UINew(fake_in("1"), fake_out(&output));
    cr_assert_eq(1, ui->read_move(ui));
}

Test(UI, ItWillReadConsecutiveMoves, .fini = teardown) {
    char* output;
    ui = UINew(fake_in("1 2"), fake_out(&output));

    cr_assert_eq(1, ui->read_move(ui));
    cr_assert_eq(2, ui->read_move(ui));
}

Test(UI, ItCanBeDestroyed) {
    char* output;
    ui = UINew(fake_in("1 2"), fake_out(&output));
    ui->destroy(ui);
}

Test(UI, ItWillRedrawTheScreen, .fini = teardown) {
    char* output;
    ui = UINew(fake_in("1 2"), fake_out(&output));
    ui->update(ui);
    cr_assert_str_eq("\033[H\033[2J", output);
}
