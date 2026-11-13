#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 12) : test < 14 ? rnd.next(100, 5000) : N_MAX;
    const int m = test < 8 ? rnd.next(1, 18) : test < 14 ? rnd.next(100, 5000) : M_MAX;
    std::cout << n << ' ' << m << '\n';
    for (int i = 0; i < n; ++i) {
        int left = rnd.next(1, m);
        int right = rnd.next(left, m);
        if (test == 14) {
            left = 1;
            right = m;
        }
        if (test == 15) left = right = m - i;
        if (test == 16) right = m;
        std::cout << left << ' ' << right << '\n';
    }
}
