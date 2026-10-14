#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int m = inf.readInt(1, M_MAX, "M");
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readEoln();
    }
    inf.readEof();
}
