#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

static void display(UI *ui, char *message) {
    fputs(message, ui->out);
    fflush(ui->out);
}

static int read_move(UI *ui) {
    int move;
    fscanf(ui->in, "%d", &move);
    return move;
}

static void destroy(UI *ui) {
    free(ui->in);
    free(ui->out);
    free(ui);
}

UI *UINew(FILE *in, FILE *out) {
    UI *ui = malloc(sizeof(UI));
    ui->in = in;
    ui->out = out;
    ui->display = display;
    ui->read_move = read_move;
    ui->destroy = destroy;
    return ui;
}
