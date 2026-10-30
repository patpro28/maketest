#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, N_MAX, "Q");
    inf.readSpace(); inf.readInt(1, A_MAX, "K");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(A_MIN, A_MAX, "A");
    }
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n, "L"); inf.readSpace();
        inf.readInt(l, n, "R"); inf.readEoln();
    }
    inf.readEof();
}
