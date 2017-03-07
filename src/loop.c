#include "game.h"
#include "stdio.h"
#include "ui.h"

void loop(Game* game, UI* ui) {
    while (game->outcome == InProgress) {
        game->move(game, ui->read_move(ui));
        ui->display(ui, "");
    }
}
