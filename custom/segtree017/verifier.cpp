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
    for (int i = 0; i < q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        inf.readInt(1, n, "position");
        inf.readSpace();
        if (type == 1) {
            inf.readInt(VALUE_MIN, VALUE_MAX, "x");
        } else {
            inf.readInt(1, n, "r");
        }
        inf.readEoln();
    }
    inf.readEof();
}
