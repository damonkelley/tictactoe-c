#ifndef __UI_H
#define __UI_H

typedef struct UI {
    int (*read)(void);
    void (*write)(char *message);
} UI;

#endif
