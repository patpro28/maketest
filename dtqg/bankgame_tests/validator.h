#pragma once
#include "testlib.h"
#include <string>
int main(int argc, char** argv) {
    registerValidation(argc, argv);
#if TASK_ID < 4
    int t = inf.readInt(1, 3, "T"); inf.readEoln();
    for (int z = 0; z < t; ++z) {
        int n = inf.readInt(1, N_MAX, "n"); inf.readSpace();
        int m = inf.readInt(n, M_MAX, "m"); inf.readEoln();
        for (int i = 0; i < n; ++i) {
            if (i) inf.readSpace();
            inf.readInt(1, VALUE_MAX, "a");
        }
        inf.readEoln();
        for (int i = 0; i < m; ++i) {
            if (i) inf.readSpace();
            inf.readInt(1, VALUE_MAX, "b");
        }
        inf.readEoln();
    }
#else
    int m = inf.readInt(1, ROWS_MAX, "m"); inf.readSpace();
    int n = inf.readInt(1, COLS_MAX, "n"); inf.readSpace();
    inf.readInt(1, 1000000000, "D"); inf.readEoln();
    std::string s = inf.readToken("[a-z]{1," + std::to_string(S_MAX) + "}", "S"); inf.readEoln();
    char first = 0;
    for (int i = 0; i < m; ++i) {
        std::string row = inf.readToken("[a-z#]{" + std::to_string(n) + "}", "row"); inf.readEoln();
        if (!i) first = row[0];
#if TASK_ID == 4
        for (char c : row) ensuref(c == '#' || c == s[0], "All letters must equal S");
#endif
    }
#if TASK_ID == 4 || TASK_ID == 5
    ensuref(first == s[0], "The starting letter must equal S");
#else
    (void)first;
#endif
#endif
    inf.readEof();
}
