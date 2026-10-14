#include "testlib.h"
#include "params.h"
int main() {
    registerValidation();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    inf.readInt(1, S_MAX, "S");
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(1, VALUE_MAX, "a_i");
        inf.readSpace();
        inf.readInt(1, VALUE_MAX, "b_i");
        inf.readEoln();
    }
    inf.readEof();
}
