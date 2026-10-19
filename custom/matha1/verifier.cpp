#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    for (int i = 0; i < t; ++i) {
        long long l = inf.readLong(1LL, LR_MAX, "L");
        inf.readSpace();
        inf.readLong(l, LR_MAX, "R");
        inf.readSpace();
        inf.readInt(1, A_MAX, "A");
        inf.readEoln();
    }
    inf.readEof();
}
