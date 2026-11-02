#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace(); inf.readLong(-S_MAX, S_MAX, "T");
    inf.readSpace(); int lower = inf.readInt(1, n, "L");
    inf.readSpace(); inf.readInt(lower, n, "R");
    (void)n;
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(A_MIN, A_MAX, "A");
    }
    inf.readEoln(); inf.readEof();
}
