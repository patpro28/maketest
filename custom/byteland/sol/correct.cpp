#include <algorithm>
#include <cstdio>
#include <numeric>
#include <vector>

struct DSU {
    std::vector<int> parent, size;

    explicit DSU(int n) : parent(n + 1), size(n + 1, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int u) {
        while (u != parent[u]) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (size[u] < size[v]) std::swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }
};

int main() {
    int n, m;
    if (std::scanf("%d%d", &n, &m) != 2) return 0;
    DSU dsu(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        dsu.unite(u, v);
    }

    const int root = dsu.find(1);
    int largest_other = 0;
    for (int u = 1; u <= n; ++u) {
        if (dsu.find(u) == u && u != root) {
            largest_other = std::max(largest_other, dsu.size[u]);
        }
    }
    std::printf("%d\n", dsu.size[root] + largest_other);
}
