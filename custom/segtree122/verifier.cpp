#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        inf.readInt(0, i - 1, "e_i");
    }
    inf.readEoln();
    inf.readEof();
}
