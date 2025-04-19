#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(0, 500'000);
    inf.readSpace();
    int m = inf.readInt(0, 500'000);
    inf.readEoln();
    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 2'000'000'000);
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }
    for (int i = 0; i < m; ++i) {
        std::string s = inf.readToken("update|get", "query");
        if (s == "update") {
            inf.readSpace();
            inf.readInt(1, n, "idx");
            inf.readSpace();
            inf.readInt(0, 2'000'000'000, "val");
            inf.readEoln();
        } else {
            inf.readSpace();
            int u = inf.readInt(1, n, "u");
            inf.readSpace();
            int v = inf.readInt(1, n, "v");
            ensure(u <= v);
            inf.readSpace();
            inf.readInt(0, 2'000'000'000, "k");
            inf.readEoln();
        }
    }
    inf.readEof();
    return 0;
}
