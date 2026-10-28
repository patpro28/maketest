#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int m = inf.readInt(1, M_MAX, "M"); inf.readSpace();
    inf.readLong(1, L_MAX, "L"); inf.readEoln();
    int total = 0;
    for (int i = 0; i < m; ++i) {
        std::string s = inf.readToken("[abc]{1,80}", "S_i");
        total += int(s.size());
        inf.readSpace(); inf.readInt(-W_MAX, W_MAX, "W_i"); inf.readEoln();
    }
    ensuref(total <= LENGTH_SUM_MAX, "Total pattern length exceeds 80");
    inf.readEof();
}
