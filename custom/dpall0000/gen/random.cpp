#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 15) : test < 14 ? rnd.next(100, 5000) : N_MAX;
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        long long fee = rnd.next(0LL, A_MAX);
        if (test == 14) fee = A_MAX;
        if (test == 15) fee = 0;
        if (test == 16) fee = i % 2 == 0 ? A_MAX : 1;
        std::cout << fee << (i + 1 == n ? '\n' : ' ');
    }
}
