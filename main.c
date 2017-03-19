#include "board.h"
#include "game.h"
#include "loop.h"
#include "presenter.h"
#include "ui.h"

int main() {
    Game* game = GameNew(BoardNew());
    UI* ui = UINew(stdin, stdout);
    loop(game, ui, present);
}
