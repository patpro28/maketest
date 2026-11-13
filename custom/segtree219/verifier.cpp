#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "A_i");
    }
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, 10000, "W_i");
    }
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int left = inf.readInt(1, n, "L");
        inf.readSpace();
        inf.readInt(left, n, "R");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(VALUE_MIN, VALUE_MAX, "X");
        }
        inf.readEoln();
    }
    inf.readEof();
}
