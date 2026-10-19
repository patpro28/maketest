#include "testlib.h"
#include "params.h"

int main(int argc, char **argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T_MAX, "T");
    inf.readEoln();
    long long sum_n = 0, sum_q = 0;
    for (int test = 0; test < t; ++test) {
        int n = inf.readInt(3, N_MAX, "N");
        inf.readSpace();
        int q = inf.readInt(1, Q_MAX, "Q");
        inf.readEoln();
        sum_n += n; sum_q += q;
        ensuref(sum_n <= SUM_N_MAX, "Sum of N exceeds the limit");
        ensuref(sum_q <= SUM_Q_MAX, "Sum of Q exceeds the limit");
        for (int i = 0; i < n; ++i) {
            if (i) inf.readSpace();
            inf.readInt(-A_MAX, A_MAX, "A_i");
        }
        inf.readEoln();
        long long groups = 1LL * n * (n - 1) * (n - 2) / 6;
        for (int i = 0; i < q; ++i) {
            inf.readLong(1LL, groups, "K");
            inf.readEoln();
        }
    }
    inf.readEof();
}
