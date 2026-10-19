#include <vector>
#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(2, N_MAX, "n");
    inf.readSpace();
    int k = inf.readInt(0, n - 1, "k");
    inf.readSpace();
    inf.readInt(0, M_MAX, "m");
    inf.readEoln();
    std::vector<bool> used(n + 1, false);
    for (int i = 0; i < k; ++i) {
        if (i) inf.readSpace();
        int b = inf.readInt(1, n, "b_i");
        ensuref(!used[b], "Slippery stairs must be distinct");
        used[b] = true;
    }
    inf.readEoln();
    inf.readEof();
}
