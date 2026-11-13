#include "../params.h"
#include "testlib.h"

enum class Pattern { pair, interior, random, sameColor, sameSize, nested };

struct Case {
    int n;
    Pattern pattern;
};

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    const Case cases[] = {
        {2, Pattern::pair}, {20, Pattern::interior}, {20, Pattern::random},
        {200, Pattern::random}, {200, Pattern::interior}, {200, Pattern::sameColor},
        {2000, Pattern::random}, {2000, Pattern::nested}, {2000, Pattern::interior},
        {50000, Pattern::nested}, {50000, Pattern::random}, {50000, Pattern::sameSize},
        {500000, Pattern::random}, {500000, Pattern::interior}, {500000, Pattern::nested},
        {N_MAX, Pattern::random}, {N_MAX, Pattern::nested}, {N_MAX, Pattern::interior},
    };
    const auto [n, pattern] = cases[opt<int>(1)];
    constexpr int limit = VALUE_MAX;
    std::ios::sync_with_stdio(false);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        int c = 0, s = 0;
        switch (pattern) {
            case Pattern::pair:
                c = s = i * limit;
                break;
            case Pattern::interior: {
                const int colors[] = {limit, limit / 2, 0, limit / 2 + 1};
                const int sizes[] = {41, 0, 40, limit};
                c = colors[i % 4];
                s = sizes[i % 4];
                break;
            }
            case Pattern::random:
                c = rnd.next(0, limit);
                s = rnd.next(0, limit);
                break;
            case Pattern::sameColor:
                c = limit;
                s = rnd.next(0, limit);
                break;
            case Pattern::sameSize:
                c = rnd.next(0, limit);
                break;
            case Pattern::nested: {
                // Visit odd positions first, then even positions, in color order.
                const int position = i < n / 2 ? 2 * i + 1 : 2 * (i - n / 2);
                const int distance = std::abs(position - n / 2);
                c = position * 41;
                s = position % 2 ? limit - 3 * distance : 2 * distance;
                break;
            }
        }
        std::cout << c << ' ' << s << '\n';
    }
}
