#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int m = inf.readInt(1, N_MAX, "M"); inf.readSpace();
    inf.readInt(1, n, "W"); inf.readEoln();
    for (int i = 1; i <= n; ++i) {
        if (i != 1) inf.readSpace();
        inf.readInt(1, m, "a_i");
    }
    inf.readEoln();
    inf.readEof();
}
