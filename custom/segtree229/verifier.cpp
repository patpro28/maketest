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
        int type = inf.readInt(0, 1, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");
        if (type == 0) {
            inf.readSpace();
            inf.readInt(VALUE_MIN, VALUE_MAX, "x");
        } else {
            ensuref(l < r, "A query needs room for two disjoint intervals");
            inf.readSpace();
            int u = inf.readInt(l, r - 1, "u");
            inf.readSpace();
            int v = inf.readInt(u, r - 1, "v");
            inf.readSpace();
            int s = inf.readInt(v + 1, r, "s");
            inf.readSpace();
            inf.readInt(s, r, "t");
            inf.readSpace();
            inf.readLong(0, 1000000000000000LL, "b");
        }
        inf.readEoln();
    }
    inf.readEof();
}
