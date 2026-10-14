#include <numeric>
#include <vector>
#include "testlib.h"

int main() {
    registerValidation();
    const int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    std::vector<int> parent(n + 1), size(n + 1, 1);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int u) {
        while (u != parent[u]) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    };

    for (int i = 0; i < n - 1; ++i) {
        int a = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        inf.readEoln();
        int u = find(a), v = find(b);
        ensuref(u != v, "Edge %d creates a cycle or a self-loop", i + 1);
        if (size[u] < size[v]) std::swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }
    inf.readEof();
    // An acyclic graph with n vertices and n-1 edges is connected.
}
