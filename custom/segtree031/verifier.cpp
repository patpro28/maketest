#include "testlib.h"
#include "params.h"
int readValue(const char *name) {
    int x = inf.readInt(VALUE_MIN, VALUE_MAX, name);
    ensuref(2520 % x == 0, "%s must divide 2520", name);
    return x;
}
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");

    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        readValue("A_i");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type"); inf.readSpace();
        int i = inf.readInt(1, n, "i_or_l"); inf.readSpace();
        if (type == 1) readValue("x");
        else inf.readInt(i, n, "r");
        inf.readEoln();
    }
    inf.readEof();
}
