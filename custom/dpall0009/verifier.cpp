#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int rows = inf.readInt(1, CELLS_MAX, "M");
    inf.readSpace();
    const int cols = inf.readInt(1, CELLS_MAX / rows, "N");
    inf.readEoln();
    for (int i = 0; i < rows; ++i) {
        inf.readInts(cols, -A_MAX, A_MAX, "A");
        inf.readEoln();
    }
    inf.readEof();
}
