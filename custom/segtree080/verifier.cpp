#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(N_MIN, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    std::string s = inf.readToken();
    ensuref(int(s.size()) == n, "S must have length N");
    for (char c : s) ensuref(c == '(' || c == ')', "S must contain only parentheses");
    inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int l = inf.readInt(1, n, "l"); inf.readSpace();
        inf.readInt(l, n, "r");
        inf.readEoln();
    }
    inf.readEof();
}
