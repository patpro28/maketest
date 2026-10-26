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
        int type = inf.readInt(1, 2, "type"); inf.readSpace();
        int i = inf.readInt(1, n, "i_or_l"); inf.readSpace();
        if (type == 1) {
            inf.readInt(VALUE_MIN, VALUE_MAX, "x");
        } else {
            inf.readInt(i, n, "r");
            inf.readSpace(); int u = inf.readInt(VALUE_MIN, VALUE_MAX, "u");
            inf.readSpace(); inf.readInt(u, VALUE_MAX, "v");
        }
        inf.readEoln();
    }
    inf.readEof();
}
