#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"

int main(int, char* argv[]) {
    Random gen(std::atoll(argv[1]));
    int n = gen.uniform(3, 10);
    std::vector<std::pair<int, int>> edges;
    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) edges.emplace_back(u, v);
    }
    gen.shuffle(edges.begin(), edges.end());
    int m = gen.uniform(1, static_cast<int>(edges.size()));
    std::printf("%d %d\n", n, m);
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edges[i];
        if (gen.uniform_bool()) std::swap(u, v);
        std::printf("%d %d\n", u, v);
    }
}
