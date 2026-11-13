#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int rows = test < 8 ? rnd.next(1, 5) : test < 14 ? rnd.next(10, 50) : R_MAX;
    const int cols = test < 8 ? rnd.next(1, 5) : test < 14 ? rnd.next(10, 50) : C_MAX;
    int turns = test < 8 ? rnd.next(0, rows + cols) : rnd.next(0LL, K_MAX);
    if (test >= 14) turns = K_MAX - (test % 2);
    std::cout << rows << ' ' << cols << ' ' << turns << '\n';
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            long long value = rnd.next(0LL, A_MAX);
            if (test == 14) value = A_MAX;
            if (test == 15) value = 0;
            if (test != 14 && test != 15 && rnd.next(0, 5) == 0 &&
                    (i != 0 || j != 0) && (i != rows - 1 || j != cols - 1)) value = -1;
            std::cout << value << (j + 1 == cols ? '\n' : ' ');
        }
    }
}
