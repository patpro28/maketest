#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, A_MAX, "A_i");
    }
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readLong(0, B_MAX, "B_i");
    }
    inf.readEoln();
    std::vector<int> parent(n);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int u) {
        while (parent[u] != u) {
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    };
    for (int i = 1; i < n; ++i) {
        int u = inf.readInt(1, n, "u") - 1;
        inf.readSpace();
        int v = inf.readInt(1, n, "v") - 1;
        inf.readSpace();
        inf.readInt(1, W_MAX, "W");
        inf.readEoln();
        int a = find(u), b = find(v);
        ensuref(a != b, "Edges must form a tree");
        parent[a] = b;
    }
    inf.readEof();
}
