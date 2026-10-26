#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace(); inf.readLong(0, W_MAX, "X");
    inf.readSpace(); inf.readLong(0, W_MAX, "Y");
    inf.readEoln();
    std::string s = inf.readToken("[AB?]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    inf.readEof();
}
