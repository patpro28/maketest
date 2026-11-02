#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    std::vector<long long> a(n + 1);

    for (int x = 1; x <= n; ++x) {
        if (x != 1) inf.readSpace(); a[x] = inf.readLong(0LL, 1000000000LL, "frequency");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 3, "type"); inf.readSpace();
        int x = inf.readInt(1, n, t == 3 ? "k" : "x");
        if (t == 2) ensuref(a[x] > 0, "Cannot remove an absent value");
        if (t <= 2) a[x] += t == 1 ? 1 : -1;
        inf.readEoln();
    }
    inf.readEof();
}
