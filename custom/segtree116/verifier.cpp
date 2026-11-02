#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    std::vector<long long> a(n + 1);

    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        a[i] = inf.readLong(1LL, 1000000000LL, "start");
        if (i > 1) ensuref(a[i - 1] < a[i], "Starts must be strictly increasing");
    }
    inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        inf.readLong(a[i], 1000000000LL, "end");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type");
        if (t == 1) {
            inf.readSpace(); int i = inf.readInt(1, n, "i");
            inf.readSpace(); inf.readLong(a[i], 1000000000LL, "end");
        }
        inf.readEoln();
    }
    inf.readEof();
}
