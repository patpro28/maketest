#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    int rows = test < 8 ? rnd.next(1, 4) : rnd.next(50, 160);
    int cols = test < 8 ? rnd.next(1, 5) : rnd.next(50, 160);
    if (test == 14) {
        rows = 1;
        cols = CELLS_MAX;
    } else if (test == 15) {
        rows = CELLS_MAX;
        cols = 1;
    } else if (test == 16) {
        rows = cols = 1000;
    } else if (test == 17) {
        rows = 500;
        cols = CELLS_MAX / rows;
    }
    std::cout << rows << ' ' << cols << '\n';
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            long long value = rnd.next(-A_MAX, A_MAX);
            if (test == 15 || test == 16) value = A_MAX;
            if (test == 17) value = -A_MAX;
            std::cout << value << (j + 1 == cols ? '\n' : ' ');
        }
    }
}
