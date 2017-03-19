#include "game.h"
#include "presenter.h"
#include "ui.h"

void loop(Game* game, UI* ui, Presenter present) {
    ui->update(ui);
    ui->display(ui, present(game));
    while (game->outcome == InProgress) {
        game->move(game, ui->read_move(ui));
        ui->update(ui);
        ui->display(ui, present(game));
    }
}
