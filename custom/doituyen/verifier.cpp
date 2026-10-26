#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int m = inf.readInt(0, M_MAX, "M");
    inf.readSpace();
    inf.readInt(1, n, "S");
    inf.readSpace();
    inf.readInt(1, n, "T");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(0, VALUE_MAX, "P_i");
    }
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "u"); inf.readSpace();
        inf.readInt(1, n, "v"); inf.readSpace();
        inf.readInt(1, VALUE_MAX, "C"); inf.readSpace();
        inf.readInt(1, VALUE_MAX, "W"); inf.readEoln();
    }
    inf.readEof();
}
