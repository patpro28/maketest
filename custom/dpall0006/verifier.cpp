#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    const int m = inf.readInt(1, M_MAX, "M");
    inf.readSpace();
    inf.readInt(0, S_MAX, "S");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "A");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(m) + "}", "B");
    inf.readEoln();
    inf.readInts(n, 1, COST_MAX, "X");
    inf.readEoln();
    inf.readInts(m, 1, COST_MAX, "Y");
    inf.readEoln();
    inf.readInts(26, 0, P_MAX, "P");
    inf.readEoln();
    inf.readEof();
}
