#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int rows = inf.readInt(1, R_MAX, "R");
    inf.readSpace();
    const int cols = inf.readInt(1, C_MAX, "C");
    inf.readSpace();
    inf.readInt(0, K_MAX, "K");
    inf.readEoln();
    for (int i = 0; i < rows; ++i) {
        inf.readInts(cols, -1, A_MAX, "A");
        inf.readEoln();
    }
    inf.readEof();
}
