#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readEoln();
    std::vector<bool> seen(n + 1);
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        int a = inf.readInt(1, n, "A_i");
        ensuref(!seen[a], "A must be a permutation"); seen[a] = true;
    }
    inf.readEoln(); inf.readEof();
}
