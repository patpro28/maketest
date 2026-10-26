#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");

    inf.readEoln();
    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        a[i] = inf.readLong(-1000000000LL, 1000000000LL, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type"); inf.readSpace();
        int i = inf.readInt(1, n, "i_or_l");
        if (t == 1) {
            inf.readSpace(); inf.readLong(-1000000000LL, 1000000000LL, "x");
        } else {
            inf.readSpace(); inf.readInt(i, n, "r");
        }
        (void)i;
        inf.readEoln();
    }
    inf.readEof();
}
