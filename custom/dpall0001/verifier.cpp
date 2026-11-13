#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    inf.readInt(0, W_MAX, "W");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(1, W_MAX, "weight");
        inf.readSpace();
        inf.readLong(0, V_MAX, "value");
        inf.readEoln();
    }
    inf.readEof();
}
