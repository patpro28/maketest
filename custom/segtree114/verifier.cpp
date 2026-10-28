#include "testlib.h"
#include "params.h"
#include <vector>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N_or_M"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "s"); inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "t"); inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            inf.readSpace(); inf.readInt(1, 2, "b");
            inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace();
            inf.readToken("[a-z]", "letter");
        }
        inf.readEoln();
    }
    inf.readEof();
}
