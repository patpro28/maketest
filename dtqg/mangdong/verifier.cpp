#include "testlib.h"
#include "params.h"
#include <algorithm>
#include <set>
#include <utility>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, 1, "C_i");
    }
    inf.readEoln();
    std::set<std::pair<int, int>> active;
    int questions = 0;
    for (int i = 0; i < q; ++i) {
        std::string op = inf.readToken("[+?\\-]", "operation");
        if (op == "?") ++questions;
        else {
            inf.readSpace(); int u = inf.readInt(1, n, "u");
            inf.readSpace(); int v = inf.readInt(1, n, "v");
            ensuref(u != v, "Self-loops are forbidden");
            if (u > v) std::swap(u, v);
            if (op == "+") ensuref(active.insert({u, v}).second, "Adding an active edge");
            else ensuref(active.erase({u, v}) == 1, "Deleting an inactive edge");
        }
        inf.readEoln();
    }
    ensuref(questions > 0, "At least one query is required");
    inf.readEof();
}
