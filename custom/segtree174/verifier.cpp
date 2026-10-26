#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    int q = inf.readInt(1, Q_MAX, "Q"); inf.readEoln();
    inf.readToken("[a-z]{" + std::to_string(n) + "}", "s"); inf.readEoln();
    for (int j = 0; j < q; ++j) {
        int t = inf.readInt(1, 2, "type");
        if (t == 1) {
            inf.readSpace(); inf.readInt(1, n, "i"); inf.readSpace();
            inf.readToken("[a-z]", "c");
        } else {
            inf.readSpace(); int l = inf.readInt(1, n, "l"); (void)l;
            inf.readSpace(); inf.readInt(1, 26, "K");
        }
        inf.readEoln();
    }
    inf.readEof();
}
