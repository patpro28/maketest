#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "a_i");
    }
    inf.readEoln();
    int m = inf.readInt(1, Q_MAX, "m"); inf.readEoln();
    for (int i = 0; i < m; ++i) {
        int type = inf.readInt(0, 1, "type"); inf.readSpace();
        int x = inf.readInt(1, n, type == 0 ? "x" : "u"); inf.readSpace();
        if (type == 0) inf.readInt(VALUE_MIN, VALUE_MAX, "y");
        else inf.readInt(x, n, "v");
        inf.readEoln();
    }
    inf.readEof();
}
