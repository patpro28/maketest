#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(PROBLEM_KIND == 19 ? 2 : 1, N_MAX, "N");
    inf.readEoln();
    if (PROBLEM_KIND == 18 || PROBLEM_KIND == 22) {
        for (int i = 0; i < n; ++i) {
            if (i) inf.readSpace();
            inf.readLong(PROBLEM_KIND == 18 ? -VALUE_MAX : 1, VALUE_MAX, "value");
        }
        inf.readEoln();
    }
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
        ensuref(u != v, "Self-loop is not allowed");
        if (PROBLEM_KIND == 19) {
            inf.readSpace();
            inf.readLong(1, VALUE_MAX, "W");
        }
        inf.readEoln();
        int a = find(u), b = find(v);
        ensuref(a != b, "Edges must form a tree: cycle or duplicate edge");
        parent[a] = b;
    }
    inf.readEof();
}
