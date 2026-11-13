#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace(); int low = inf.readInt(1, n, "low");
    inf.readSpace(); inf.readInt(low, n, "R");
    inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    inf.readEof();
}
