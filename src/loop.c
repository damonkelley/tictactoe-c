#include "game.h"
#include "presenter.h"
#include "stdio.h"
#include "ui.h"

void loop(Game* game, UI* ui, Presenter present) {
    ui->display(ui, present(game));
    int move;
    while (game->outcome == InProgress) {
        move = ui->read_move(ui);
        game->move(game, move);
        ui->display(ui, present(game));
    }
}
