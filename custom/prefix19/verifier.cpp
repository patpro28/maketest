#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(3, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(-A_MAX, A_MAX, "value");
    }
    inf.readEoln();
    inf.readEof();
}
