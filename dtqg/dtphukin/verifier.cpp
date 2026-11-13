#include "testlib.h"
#include "params.h"

int main(int argc, char** argv) {
    registerValidation(argc, argv);

    int tests = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    int total = 0;
    for (int i = 0; i < tests; ++i) {
        int n = inf.readInt(1, N_MAX, "N");
        inf.readEoln();
        total += n;
        ensuref(total <= SUM_N_MAX, "The total of N exceeds %lld", SUM_N_MAX);
        inf.readInts(n, 0, 1, "A");
        inf.readEoln();
    }
    inf.readEof();
}
