typedef struct Board {
    char spaces[9];
    int (*add)(struct Board *self, char marker, int space);
    char (*get)(struct Board *self, int space);
    void (*destroy)(struct Board *self);
} Board;

Board *BoardNew();
