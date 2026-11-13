#include "testlib.h"
#include "params.h"

void read_row(int length, const char* name) {
    for (int i = 0; i < length; ++i) {
        if (i > 0) inf.readSpace();
        inf.readLong(-VALUE_MAX, VALUE_MAX, name);
    }
    inf.readEoln();
}

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    long long total_n = 0;
    for (int test = 1; test <= t; ++test) {
        setTestCase(test);
        int n = inf.readInt(1, N_MAX, "N");
        total_n += n;
        ensuref(total_n <= N_MAX, "sum of N exceeds %lld", N_MAX);
        inf.readEoln();
        read_row(n, "A");
    }
    inf.readEof();
}
