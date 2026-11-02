#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int m = inf.readInt(1, M_MAX, "M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) inf.readSpace();
            inf.readInt(A_MIN, A_MAX, "A");
        }
        inf.readEoln();
    }
    for (int i = 0; i < q; ++i) {
        int x1 = inf.readInt(1, n, "X1"); inf.readSpace();
        int y1 = inf.readInt(1, m, "Y1"); inf.readSpace();
        inf.readInt(x1, n, "X2"); inf.readSpace();
        inf.readInt(y1, m, "Y2"); inf.readEoln();
    }
    inf.readEof();
}
