#include "testlib.h"
#include "params.h"
#include <algorithm>
int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int n = inf.readInt(1, N_MAX, "N"); inf.readSpace();
    inf.readInt(1, std::min<int>(K_MAX, n), "K"); inf.readEoln();
    for (int i = 0; i < n; ++i) {
        if (i) inf.readSpace();
        inf.readInt(1, n, "A_i");
    }
    inf.readEoln(); inf.readEof();
}
