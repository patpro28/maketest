#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    std::string s = inf.readToken("[ab]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    inf.readEof();
}
