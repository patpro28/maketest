#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(0, Q_MAX, "Q");
    inf.readSpace(); inf.readInt(1, n, "S");
    inf.readSpace(); inf.readInt(1, n, "T");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n, "l_i"); inf.readSpace();
        inf.readInt(l, n, "r_i"); inf.readSpace();
        int a = inf.readInt(1, n, "a_i"); inf.readSpace();
        inf.readInt(a, n, "b_i"); inf.readSpace();
        inf.readInt(0, VALUE_MAX, "c_i");
        inf.readEoln();
    }
    inf.readEof();
}
