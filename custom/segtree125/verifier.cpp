#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "s"); inf.readEoln();
    std::vector<long long> frequency(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        frequency[i] = inf.readLong(0LL, 1000000000LL, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace();
            inf.readToken("[a-z]", "letter");
            inf.readSpace(); inf.readInt(0, VALUE_MAX, "count");
        } else { inf.readSpace(); inf.readLong(1LL, 1000000000000000000LL, "k"); }
        inf.readEoln();
    }
    inf.readEof();
}
