#include "testlib.h"
#include "params.h"
int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int rows = inf.readInt(1, SIDE_MAX, "R"); inf.readSpace();
    int columns = inf.readInt(1, SIDE_MAX, "C"); inf.readEoln();
    ensuref(1LL * rows * columns <= CELLS_MAX, "Too many cells");
    for (int i = 0; i < rows; ++i) {
        std::string s = inf.readToken("[01]+", "row");
        ensuref(int(s.size()) == columns, "Invalid row length"); inf.readEoln();
    }
    inf.readEof();
}
