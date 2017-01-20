#include "tictactoe.h"
#include <criterion/criterion.h>

Test(example, add) {
    cr_assert_eq(add(1, 1), 2);
}
