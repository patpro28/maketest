#include "testlib.h"
#include "params.h"

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int m = inf.readInt(2, M_SINGLE_MAX, "M");
    inf.readEoln();
    int maxColumns = n == 1 ? M_SINGLE_MAX : (n == 2 ? M_DOUBLE_MAX : M_MAX);
    ensuref(m <= maxColumns, "M is too large for N");
    int bananas = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j != 0 && inf.curChar() == ' ') inf.readSpace();
            char cell = inf.readChar();
            ensuref(cell == '0' || cell == '1', "Expected a binary cell");
            bananas += cell == '1';
        }
        inf.readEoln();
    }
    inf.readEof();
    ensuref(bananas > 0 && bananas < n * m, "Both tree types must occur");
}
