#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readSpace(); long long u = inf.readLong(-S_MAX, S_MAX, "U");
    inf.readSpace(); inf.readLong(u, S_MAX, "V");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(A_MIN, A_MAX, "A");
    }
    inf.readEoln();
    inf.readEof();
}
