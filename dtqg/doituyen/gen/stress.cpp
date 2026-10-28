#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"

struct Edge { int u, v, c, w; };

int main(int argc, char **argv) {
    const int seed = argc > 1 ? std::atoi(argv[1]) : 0;
    const int m = int(M_MAX);
    if (seed < 0 || seed > 5) return 1;
    if (seed == 5) {
        const int incoming = (m - 1) / 2;
        std::cout << "3 " << m << " 1 3\n0 " << VALUE_MAX << " 0\n";
        for (int i = 1; i <= incoming; ++i)
            std::cout << "1 2 " << i << " 1\n";
        for (int i = incoming + 1; i < m; ++i)
            std::cout << "2 2 " << i << " 1\n";
        std::cout << "2 3 " << VALUE_MAX << ' ' << VALUE_MAX << '\n';
        return 0;
    }
    if (seed >= 3) {
        const int k = m / 3;
        const int n = 2 * k + 2;
        const int target = k + 2;
        std::vector<Edge> edges;
        for (int i = 0; i < k; ++i) {
            int a = 2 + i, b = k + 2 + i;
            edges.push_back({0, a, i + 1, seed == 3 ? 1 : i + 1});
            edges.push_back({a, 1, i + 1, 1});
            edges.push_back({1, b, k + i + 1, seed == 3 ? 100 : int(VALUE_MAX)});
        }
        std::vector<int> label(n);
        std::iota(label.begin(), label.end(), 0);
        if (seed == 4) {
            Random rng(2026102604ULL);
            for (int i = n - 1; i > 0; --i) std::swap(label[i], label[rng.uniform(0, i)]);
            for (int i = int(edges.size()) - 1; i > 0; --i)
                std::swap(edges[i], edges[rng.uniform(0, i)]);
        }
        std::cout << n << ' ' << edges.size() << ' ' << label[0] + 1 << ' ' << label[target] + 1 << '\n';
        for (int i = 0; i < n; ++i)
            std::cout << (i ? " " : "") << (i == label[1] ? VALUE_MAX : 0);
        std::cout << '\n';
        for (auto e : edges)
            std::cout << label[e.u] + 1 << ' ' << label[e.v] + 1 << ' ' << e.c << ' ' << e.w << '\n';
        return 0;
    }
    if (seed < 2) {
        std::cout << "3 " << m << " 1 3\n0 " << VALUE_MAX << " 0\n";
        for (int i = 1; i <= m / 2; ++i)
            std::cout << "1 2 " << (seed == 1 ? 1 : i) << " 1\n";
        for (int i = m / 2 + 1; i <= m; ++i)
            std::cout << "2 3 " << (seed == 1 ? 1 : i) << " 1\n";
    } else {
        std::cout << "2 " << m << " 1 2\n0 0\n";
        for (int i = 1; i < m; ++i)
            std::cout << "1 1 " << i << " 1\n";
        std::cout << "1 2 " << VALUE_MAX << " 1\n";
    }
}
