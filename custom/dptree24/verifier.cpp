#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    if (PROBLEM_KIND == 23) {
        for (int i = 0; i < n; ++i) {
            if (i) inf.readSpace();
            inf.readLong(1, VALUE_MAX, "C");
        }
        inf.readEoln();
    }
    if (PROBLEM_KIND == 24) {
        for (int i = 0; i < n; ++i) {
            inf.readLong(0, VALUE_MAX, "A"); inf.readSpace();
            inf.readLong(0, VALUE_MAX, "B"); inf.readEoln();
        }
    }
    std::vector<int> parent(n), size(n, 1);
    std::iota(parent.begin(), parent.end(), 0);
    auto find = [&](int u) {
        while (parent[u] != u) {
            parent[u] = parent[parent[u]]; u = parent[u];
        }
        return u;
    };
    for (int i = 1; i < n; ++i) {
        int u = inf.readInt(1, n, "u") - 1; inf.readSpace();
        int v = inf.readInt(1, n, "v") - 1;
        ensuref(u != v, "Self-loop is not allowed");
        if (PROBLEM_KIND == 24) {
            inf.readSpace(); inf.readLong(0, VALUE_MAX, "W");
        }
        inf.readEoln();
        int a = find(u), b = find(v);
        ensuref(a != b, "Edges must form a tree: cycle or duplicate edge");
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a; size[a] += size[b];
    }
    inf.readEof();
}
