#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

int representative(std::vector<int>& parent, int u) {
    while (parent[u] != u) {
        parent[u] = parent[parent[u]];
        u = parent[u];
    }
    return u;
}

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readSpace();
    int m = inf.readInt(1, M_MAX, "M");
    inf.readEoln();

    for (int u = 1; u <= n; ++u) {
        if (u > 1) inf.readSpace();
        inf.readInt(1, k, "c_i");
    }
    inf.readEoln();

    std::vector<int> parent(n + 1), size(n + 1, 1);
    std::iota(parent.begin(), parent.end(), 0);
    for (int i = 1; i < n; ++i) {
        int u = inf.readInt(1, n, "a_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "b_i");
        inf.readEoln();
        u = representative(parent, u);
        v = representative(parent, v);
        ensuref(u != v, "Road %d creates a cycle", i);
        if (size[u] < size[v]) std::swap(u, v);
        parent[v] = u;
        size[u] += size[v];
    }

    for (int i = 0; i < m; ++i) {
        int type = inf.readInt(STATIC_GUARDS ? 2 : 1, 2, "type");
        inf.readSpace();
        inf.readInt(1, n, "city");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(1, k, "new_guard");
        }
        inf.readEoln();
    }
    inf.readEof();
}
