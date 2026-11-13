#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 7) : test < 14 ? rnd.next(20, 80) : N_MAX;
    const int m = test < 8 ? rnd.next(1, 7) : test < 14 ? rnd.next(20, 80) : M_MAX;
    const int budget = test < 8 ? rnd.next(0, 20) : test < 14 ? rnd.next(20, 100) : S_MAX;
    std::cout << n << ' ' << m << ' ' << budget << '\n';
    for (int word = 0; word < 2; ++word) {
        for (int i = 0; i < (word == 0 ? n : m); ++i) {
            char ch = static_cast<char>('a' + rnd.next(0, test % 3 + 1));
            if (test == 14 || test == 15) ch = 'a';
            if (test == 16) ch = word == 0 ? 'a' : 'b';
            std::cout << ch;
        }
        std::cout << '\n';
    }
    for (int length : {n, m}) {
        for (int i = 0; i < length; ++i) {
            int cost = rnd.next(1, 7);
            if (test == 14) cost = 1;
            if (test == 15) cost = COST_MAX;
            std::cout << cost << (i + 1 == length ? '\n' : ' ');
        }
    }
    for (int i = 0; i < 26; ++i) {
        const long long points = test == 14 ? P_MAX : rnd.next(0LL, P_MAX);
        std::cout << points << (i == 25 ? '\n' : ' ');
    }
}
