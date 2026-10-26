#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(N_MIN, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "A_i");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int l = inf.readInt(1, n, "l"); inf.readSpace();
        inf.readInt(l, n, "r");
        inf.readEoln();
    }
    inf.readEof();
}
