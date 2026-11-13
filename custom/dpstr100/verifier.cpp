#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int m = inf.readInt(1, M_MAX, "M");
    inf.readEoln();
    inf.readToken("[abcdefghijklmnopqrstuvwxyz]{" + std::to_string(n) + "}", "A"); inf.readEoln();
    inf.readToken("[abcdefghijklmnopqrstuvwxyz]{" + std::to_string(m) + "}", "B"); inf.readEoln();
    inf.readEof();
}
