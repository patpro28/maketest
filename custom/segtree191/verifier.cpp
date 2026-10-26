#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, n, "Q");

    inf.readEoln();

    for (int j = 0; j < q; ++j) {
        inf.readLong(1LL, 1000000000000000000LL, "k");
        inf.readEoln();
    }
    inf.readEof();
}
