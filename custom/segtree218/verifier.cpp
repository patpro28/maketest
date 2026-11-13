#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = 1000000000;
    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int left = inf.readInt(1, n, "L");
        inf.readSpace();
        inf.readInt(left, n, "R");
        if (type == 1) {
            inf.readSpace();
            inf.readInt(VALUE_MIN, VALUE_MAX, "X");
        }
        inf.readEoln();
    }
    inf.readEof();
}
