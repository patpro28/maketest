#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(VALUE_MIN, VALUE_MAX, "A_i");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) { inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace(); inf.readInt(VALUE_MIN, VALUE_MAX, "x"); }
        else { inf.readSpace(); inf.readInt(1, n, "l"); inf.readSpace(); inf.readLong(0, 1000000000000000000LL, "B");
            inf.readSpace(); inf.readInt(0, 1000000000, "D"); }
        inf.readEoln();
    }
    inf.readEof();
}
