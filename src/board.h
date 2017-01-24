typedef struct Board {
    char spaces[9];
    int (*add)(struct Board *self, char marker, int space);
    void (*destroy)(struct Board *self);
} Board;

Board *board_new();
