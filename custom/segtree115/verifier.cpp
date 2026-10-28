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
        frequency[i] = inf.readLong(-1000000000LL, 1000000000LL, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace();
            inf.readInt(-1000000000, 1000000000, "x");
        }
        inf.readEoln();
    }
    inf.readEof();
}
