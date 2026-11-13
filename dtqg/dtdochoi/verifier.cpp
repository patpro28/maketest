#include "params.h"
#include "testlib.h"

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(2, N_MAX, "n");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(0, VALUE_MAX, "c_i");
        inf.readSpace();
        inf.readInt(0, VALUE_MAX, "s_i");
        inf.readEoln();
    }
    inf.readEof();
}
