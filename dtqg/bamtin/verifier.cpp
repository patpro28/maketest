#include "testlib.h"
#include "params.h"
int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        int l = inf.readInt(-VALUE_MAX, VALUE_MAX, "L_i"); inf.readSpace();
        inf.readInt(l, VALUE_MAX, "R_i"); inf.readEoln();
    }
    for (int i = 0; i + 1 < n; ++i) {
        inf.readInt(0, VALUE_MAX, "U_i"); inf.readSpace();
        inf.readInt(0, VALUE_MAX, "V_i"); inf.readEoln();
    }
    inf.readEof();
}
