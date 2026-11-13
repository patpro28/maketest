#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 7) : test < 14 ? rnd.next(30, 100) : N_MAX;
    const int target = test < 8 ? rnd.next(0, 16) : test < 14 ? rnd.next(100, 1000) : W_MAX;
    std::cout << n << ' ' << target << '\n';
    for (int i = 0; i < n; ++i) {
        int type = rnd.next(0, 1);
        int weight = rnd.next(1, std::max(1, target / 2));
        long long value = rnd.next(0LL, test % 2 == 0 ? 8LL : V_MAX);
        if (test == 14 || test == 15) {
            type = test == 14 ? 1 : i % 2;
            weight = 1;
            value = test == 14 ? V_MAX : 0;
        }
        if (test == 16) weight = 3 * rnd.next(1, 100);
        std::cout << type << ' ' << weight << ' ' << value << '\n';
    }
}
