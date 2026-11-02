#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
    int m = inf.readInt(1, Q_MAX, "m"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace(); inf.readInt(VALUE_MIN, VALUE_MAX, "a_i");
    }
    inf.readEoln();
    for (int j = 0; j < m; ++j) {
        int type = inf.readInt(0, 1, "type"); inf.readSpace();
        int u = inf.readInt(1, n, "u"); inf.readSpace(); inf.readInt(u, n, "v");
        if (type == 0) { inf.readSpace(); inf.readInt(VALUE_MIN, VALUE_MAX, "k"); }
        inf.readEoln();
    }
    inf.readEof();
}
