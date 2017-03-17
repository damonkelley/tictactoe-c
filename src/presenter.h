#ifndef __PRESENTER_H
#define __PRESENTER_H

#include <stdbool.h>
#include "game.h"

typedef char *(*Presenter)(Game *game);

char *present(Game *game);
#endif
