#include "testlib.h"
#include "params.h"
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    while (t--) {
        int n = inf.readInt(1, N_MAX, "n");
        inf.readEoln();
        for (int row = 0; row < 3; ++row) {
            int len = row == 2 ? n : n-1;
            for (int i = 0; i < len; ++i) {
                if (i) inf.readSpace();
                inf.readInt(1, COST_MAX, "cost");
            }
            inf.readEoln();
        }
    }
    inf.readEof();
}
