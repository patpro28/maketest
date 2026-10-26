#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    std::string s = inf.readToken("[RGB]{" + std::to_string(n) + "}", "S");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readLong(0, W_MAX, "W_i");
    }
    inf.readEoln();
    inf.readEof();
}
