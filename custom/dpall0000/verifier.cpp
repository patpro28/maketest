#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    inf.readInts(n, 0, A_MAX, "A");
    inf.readEoln();
    inf.readEof();
}
