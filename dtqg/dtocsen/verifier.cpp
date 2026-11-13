#include "testlib.h"
#include "params.h"

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    inf.readLong(1, H_MAX, "H");
    inf.readSpace();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i != 0) inf.readSpace();
        inf.readLong(-P_MAX, P_MAX, "P");
    }
    inf.readEoln();
    inf.readEof();
}
