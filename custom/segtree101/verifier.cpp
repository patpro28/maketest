#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");

    inf.readEoln();
    std::vector<long long> a(n + 2);
    for (int i = 0; i <= n; ++i) {
        if (i != 0) inf.readSpace();
        a[i] = inf.readLong(0LL, 1000000000LL, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type"); inf.readSpace();
        int x = inf.readInt(0, n, "x");
        if (t == 2) { ensuref(a[x] > 0, "cannot delete absent value"); --a[x]; }
        else ++a[x];
        inf.readEoln();
    }
    inf.readEof();
}
