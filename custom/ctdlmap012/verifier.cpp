#include "testlib.h"
#include "params.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    const int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readLong(-A_MAX, A_MAX, "A_i");
        if (i + 1 < n) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
}
