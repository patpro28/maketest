#include "testlib.h"
#include "params.h"
int main() {
    registerValidation();
    int t = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    for (int i = 0; i < t; ++i) {
        inf.readInt(2, N_MAX, "N");
        inf.readSpace();
        inf.readInt(1, S_MAX, "S");
        inf.readEoln();
    }
    inf.readEof();
}
