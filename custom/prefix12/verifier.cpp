#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_MAX, "Q");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    for (int t = 0; t < q; ++t) {
        int l = inf.readInt(1, n, "L"); inf.readSpace();
        inf.readInt(l, n, "R");
        inf.readSpace(); inf.readToken("[a-z]", "c");
        inf.readEoln();
    }
    inf.readEof();
}
