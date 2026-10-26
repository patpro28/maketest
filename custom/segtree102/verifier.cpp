#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        inf.readInt(0, 1048575, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type");
        if (t == 1) {
            inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace();
            inf.readInt(0, 1048575, "x");
        } else {
            inf.readSpace(); inf.readInt(1, 1048575, "M");
        }
        inf.readEoln();
    }
    inf.readEof();
}
