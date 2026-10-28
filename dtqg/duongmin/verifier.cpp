#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>
int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, VALUE_MAX, "A_u");
    }
    inf.readEoln();
    std::vector<int> parent(n); std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int u) {
        while (parent[u] != u) { parent[u] = parent[parent[u]]; u = parent[u]; }
        return u;
    };
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u = inf.readInt(1, n, "u") - 1; inf.readSpace();
        int v = inf.readInt(1, n, "v") - 1; inf.readEoln();
        int a = find(u), b = find(v);
        ensuref(a != b, "Edges must form a tree"); parent[a] = b;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    std::vector<int> depth(n), order{0}; depth[0] = 1;
    for (int i = 0; i < n; ++i) for (int v : adj[order[i]]) if (!depth[v]) {
        depth[v] = depth[order[i]] + 1; order.push_back(v);
    }
    for (int i = 0; i < q; ++i) {
        int v = inf.readInt(1, n, "v") - 1; inf.readSpace();
        inf.readInt(1, depth[v], "k"); inf.readEoln();
    }
    inf.readEof();
}
