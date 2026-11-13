#include "testlib.h"
#include "../params.h"

#include <iostream>

int main(int argc, char **argv) {
    registerGen(argc, argv, 1);
    const int test = opt<int>(1);

    const int n = test < 8 ? rnd.next(1, 12) : test < 14 ? rnd.next(30, 350) : N_MAX;
    const int m = test < 8 ? rnd.next(1, 12) : test < 14 ? rnd.next(30, 350) : M_MAX;
    const int alphabet = test % 3 == 0 ? 2 : test % 3 == 1 ? 4 : 26;
    std::cout << n << ' ' << m << '\n';
    for (int word = 0; word < 2; ++word) {
        for (int i = 0; i < (word == 0 ? n : m); ++i) {
            char ch = static_cast<char>('a' + rnd.next(0, alphabet - 1));
            if (test == 14) ch = 'a';
            if (test == 15) ch = word == 0 ? 'a' : 'b';
            if (test == 16) ch = static_cast<char>('a' + (i + word) % 2);
            std::cout << ch;
        }
        std::cout << '\n';
    }
}
