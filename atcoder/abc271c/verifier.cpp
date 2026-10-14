#include "testlib.h"
#include "params.h"
int main() {
    registerValidation();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(1, A_MAX, "a_i");
    }
    inf.readEoln();
    inf.readEof();
}
