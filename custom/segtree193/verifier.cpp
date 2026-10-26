#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int c = inf.readInt(1, N_MAX, "C"); inf.readSpace();
    int n = inf.readInt(0, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        inf.readInt(0, c, "initial");
    }
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type");
        inf.readSpace(); inf.readInt(t == 1 ? 0 : 1, c, "capacity_or_size");
        inf.readEoln();
    }
    inf.readEof();
}
