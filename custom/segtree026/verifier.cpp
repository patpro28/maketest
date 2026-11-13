#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n");
    inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "a_i");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "position");
        inf.readSpace();
        if (type == 1) {
            inf.readInt(VALUE_MIN, VALUE_MAX, "x");
        } else {
            int r = inf.readInt(l, n, "r");
            inf.readSpace();
            int u = inf.readInt(l, r, "u");
            inf.readSpace();
            int v = inf.readInt(u, r, "v");
            ensuref(l < u || v < r, "The exclusion must leave at least one position");
        }
        inf.readEoln();
    }
    inf.readEof();
}
