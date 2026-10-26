#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(-A_MAX, A_MAX, "value");
    }
    inf.readEoln();
    for (int t = 0; t < q; ++t) {
        inf.readInt(1, n, "L"); inf.readSpace();
        inf.readInt(1, n, "K");
        inf.readEoln();
    }
    inf.readEof();
}
