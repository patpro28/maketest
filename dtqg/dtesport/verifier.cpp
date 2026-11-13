#include "testlib.h"
#include "params.h"

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i != 0) inf.readSpace();
        inf.readInt(-VALUE_MAX, VALUE_MAX, "D");
    }
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "L");
        inf.readSpace();
        inf.readInt(l, n, "R");
        if (type != 3) {
            inf.readSpace();
            inf.readInt(-VALUE_MAX, VALUE_MAX, "S");
            inf.readSpace();
            inf.readInt(-VALUE_MAX, VALUE_MAX, "C");
        }
        inf.readEoln();
    }
    inf.readEof();
}
