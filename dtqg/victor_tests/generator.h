#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

enum Shape { Path, Star, Binary, Random, Broom };

int main(int argc, char** argv) {
    registerGen(argc, argv, 1);
    int seed = std::atoi(argv[1]);
    ensuref(0 <= seed && seed < 22, "Unknown case %d", seed);

    int n, m, k;
    Shape shape;
    if (seed < 8) {
        const int nodes[] = {1, 1, 2, 6, 7, 10, 17, 24};
        const int events[] = {1, 12, 14, 28, 32, 40, 50, 60};
        const Shape shapes[] = {Path, Path, Path, Path, Binary, Star, Binary, Broom};
        n = nodes[seed];
        m = events[seed];
        shape = shapes[seed];
        k = seed == 3 ? 2 : n;
    } else if (seed < 14) {
        n = rnd.next(30, 80);
        m = rnd.next(90, 170);
        k = rnd.next(1, n);
        shape = static_cast<Shape>((seed - 8) % 5);
    } else {
        n = N_MAX;
        m = M_MAX;
        const Shape shapes[] = {Path, Path, Star, Binary, Random, Binary, Star, Broom};
        shape = shapes[seed - 14];
        k = seed == 14 ? 1 : n;
    }

    std::vector<int> label(n + 1), guard(n + 1);
    std::iota(label.begin(), label.end(), 0);
    shuffle(label.begin() + 2, label.end());
    for (int u = 1; u <= n; ++u) {
        guard[u] = (seed == 2 || seed == 5 || seed == 16 || seed == 19 || seed == 20)
            ? u : rnd.next(1, k);
        if (seed == 6 || seed == 7 || seed == 21) guard[u] = 1 + u % std::min(k, 7);
    }

    std::vector<std::pair<int, int>> roads;
    roads.reserve(n - 1);
    for (int u = 2; u <= n; ++u) {
        int p = 1;
        switch (shape) {
            case Path: p = u - 1; break;
            case Star: break;
            case Binary: p = u / 2; break;
            case Random: p = rnd.next(1, u - 1); break;
            case Broom: p = std::min(u - 1, n / 2); break;
        }
        if (rnd.next(0, 1)) roads.emplace_back(label[p], label[u]);
        else roads.emplace_back(label[u], label[p]);
    }
    shuffle(roads.begin(), roads.end());

    std::ios::sync_with_stdio(false);
    std::cout << n << ' ' << k << ' ' << m << '\n';
    std::vector<int> byLabel(n + 1);
    for (int u = 1; u <= n; ++u) byLabel[label[u]] = guard[u];
    for (int u = 1; u <= n; ++u) std::cout << byLabel[u] << (u == n ? '\n' : ' ');
    for (const auto& road : roads) std::cout << road.first << ' ' << road.second << '\n';

    for (int i = 0; i < m; ++i) {
        int u = rnd.next(1, n);
        bool update = !STATIC_GUARDS && seed != 0 && seed != 14 && i % 5 != 0;
        if (!STATIC_GUARDS && seed == 20) update = true;
        if (seed == 14 && i % 2 == 0) {
            u = 1;
        } else if (seed == 15 || seed == 21) {
            if (i % 16 == 0) u = 1;
            else if (!update && i % 1009 == 0) u = n / 3;
            else if (!update) u = rnd.next(n - 127, n);
        } else if (i % 16 == 0) {
            u = 1;
        }
        if (update) {
            int color = rnd.next(1, k);
            if (seed == 6 || seed == 7 || seed == 21) color = rnd.next(1, 7);
            if (seed == 2 || seed == 5 || seed == 19) color = i % 2 ? 1 : u;
            if (seed == 4 && i % 4 == 1) color = k;
            if (i % 11 == 0) color = guard[u];
            std::cout << "1 " << label[u] << ' ' << color << '\n';
            guard[u] = color;
        } else {
            std::cout << "2 " << label[u] << '\n';
        }
    }
}
