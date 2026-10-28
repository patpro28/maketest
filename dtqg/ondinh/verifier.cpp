#include "testlib.h"
#include "params.h"
int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(0, VALUE_MAX, "A_i"); inf.readSpace();
        inf.readInt(1, VALUE_MAX, "W_i"); inf.readEoln();
    }
    if (n > 1) {
        for (int i = 0; i + 1 < n; ++i) {
            if (i) inf.readSpace();
            inf.readInt(1, VALUE_MAX, "C_i");
        }
        inf.readEoln();
    }
    inf.readEof();
}
