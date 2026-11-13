#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    const int m = inf.readInt(1, M_MAX, "M");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        const int left = inf.readInt(1, m, "L");
        inf.readSpace();
        inf.readInt(left, m, "R");
        inf.readEoln();
    }
    inf.readEof();
}
