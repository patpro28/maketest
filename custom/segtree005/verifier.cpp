#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, M_MAX, "m"); inf.readEoln();
    for (int i = 0; i < m; ++i) {
        int u = inf.readInt(1, n, "u"); inf.readSpace();
        inf.readInt(u, n, "v"); inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "k"); inf.readEoln();
    }
    int q = inf.readInt(1, Q_MAX, "q"); inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int u = inf.readInt(1, n, "u"); inf.readSpace();
        inf.readInt(u, n, "v"); inf.readEoln();
    }
    inf.readEof();
}
