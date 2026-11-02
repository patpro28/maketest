#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "s_i");
    }
    inf.readEoln();
    int m = inf.readInt(1, Q_MAX, "m"); inf.readEoln();
    for (int i = 0; i < m; ++i) {
        int l = inf.readInt(1, n, "L"); inf.readSpace();
        inf.readInt(l, n, "R"); inf.readEoln();
    }
    inf.readEof();
}
