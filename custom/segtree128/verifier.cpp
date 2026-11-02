#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    std::vector<long long> a(n + 1);

    for (int j = 0; j < q; ++j) {
        inf.readInt(1, 2, "type"); inf.readSpace(); inf.readInt(1, n, "x_or_k"); inf.readEoln();
    }
    inf.readEof();
}
