#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(0, Q_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(1, VALUE_MAX, "d_i");
    }
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n, "l_i"); inf.readSpace();
        inf.readInt(l, n, "r_i"); inf.readSpace();
        inf.readInt(1, n, "u_i");
        inf.readEoln();
    }
    inf.readEof();
}
