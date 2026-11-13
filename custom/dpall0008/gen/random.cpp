#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 16) : test < 14 ? rnd.next(100, 5000) : N_MAX;
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int color = rnd.next(0, 2);
        if (test == 14 || test == 15) color = i % 3;
        if (test == 16) color = 0;
        std::cout << static_cast<char>('A' + color);
    }
    std::cout << '\n';
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            long long score = rnd.next(-W_MAX, W_MAX);
            if (test == 14) score = W_MAX;
            if (test == 15) score = (x + 1) % 3 == y ? -W_MAX : W_MAX;
            if (test == 16) score = -W_MAX;
            std::cout << score << (y == 2 ? '\n' : ' ');
        }
    }
}
