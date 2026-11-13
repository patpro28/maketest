#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    const int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    inf.readToken("[ABC]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    for (int i = 0; i < 3; ++i) {
        inf.readInts(3, -W_MAX, W_MAX, "W");
        inf.readEoln();
    }
    inf.readEof();
}
