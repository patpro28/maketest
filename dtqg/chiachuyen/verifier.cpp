#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int l = inf.readInt(1, n, "L");
    inf.readSpace();
    inf.readInt(l, n, "R");
    inf.readSpace();
    inf.readInt(0, VALUE_MAX, "C");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(1, VALUE_MAX, "H_i");
    }
    inf.readEoln();
    inf.readEof();
}
