#include "testlib.h"
#include "params.h"
int main() {
    registerValidation();
    int m = inf.readInt(1, M_MAX, "M");
    inf.readSpace();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j) inf.readSpace();
            inf.readInt(0, 1, "cell");
        }
        inf.readEoln();
    }
    inf.readEof();
}
