#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    const int m = inf.readInt(1, M_MAX, "M");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "A");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(m) + "}", "B");
    inf.readEoln();
    inf.readEof();
}
