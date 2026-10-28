#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    std::vector<long long> frequency(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        frequency[i] = inf.readLong(0LL, 1000000000LL, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 3, "type");
        if (type <= 2) {
            inf.readSpace(); int x = inf.readInt(1, n, "x");
            if (type == 2) { ensuref(frequency[x] > 0, "cannot delete absent value"); --frequency[x]; }
            else ++frequency[x];
        } else { inf.readSpace(); inf.readInt(1, n, "k"); }
        inf.readEoln();
    }
    inf.readEof();
}
