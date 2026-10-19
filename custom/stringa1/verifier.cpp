#include <string>
#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    inf.readInt(1, K_MAX, "K");
    inf.readEoln();
    std::string s = inf.readToken("[a-zA-Z0-9]{1,100000}", "S");
    ensuref(static_cast<int>(s.size()) <= N_MAX, "String too long");
    inf.readEoln();
    inf.readEof();
}
