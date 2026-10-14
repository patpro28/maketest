#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int argc, char* argv[]) {
    assert(argc == 2);
    const int seed = std::atoi(argv[1]);
    assert(0 <= seed && seed < 8);
    Random rng(seed + 12012);
    std::vector<long long> a;
    switch (seed) {
    case 0: a = {1, 6, 2, 5, 3}; break;
    case 1: a = {0, 0, 0, 0}; break;
    case 2: a = {1, 2, 3, 2}; break;
    case 3: a = {A_MAX, -A_MAX, -A_MAX, A_MAX}; break;
    case 4: a.assign(7, A_MAX); break;
    case 5:
        for (int i = 0; i < 100; ++i) a.push_back(i - 50);
        break;
    case 6:
        for (int i = 0; i < 100; ++i) a.push_back(rng.uniform<long long>(-3, 3));
        break;
    case 7:
        for (int i = 0; i < 100; ++i) a.push_back(rng.uniform<long long>(-A_MAX, A_MAX));
        a[0] = A_MAX;
        a[1] = -A_MAX;
        a[98] = -A_MAX;
        a[99] = A_MAX;
        break;
    }
    std::cout << a.size() << '\n';
    for (std::size_t i = 0; i < a.size(); ++i)
        std::cout << a[i] << (i + 1 == a.size() ? '\n' : ' ');
}
