#include <algorithm>
#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int k = inf.readInt(1, std::min<long long>(n, K_MAX), "k"); inf.readEoln();
    for (int i = 0; i < k; ++i) {
        if (i) inf.readSpace();
        inf.readInt(-A_MAX, A_MAX, "a");
    }
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(-X_MAX, X_MAX, "x");
    }
    inf.readEoln(); inf.readEof();
}
