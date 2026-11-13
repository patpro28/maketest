#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace(); int low = inf.readInt(1, 1000000000, "low");
    inf.readSpace(); inf.readInt(low, 1000000000, "R");
    inf.readEoln();
    inf.readToken("[0-9]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    inf.readEof();
}
