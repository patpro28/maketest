#include "testlib.h"

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt(), query_number = 0;
    for (int test = 1; test <= t; ++test) {
        int n = inf.readInt(), q = inf.readInt();
        for (int i = 0; i < n; ++i) inf.readInt();
        for (int i = 0; i < q; ++i) {
            inf.readLong();
            ++query_number;
            int expected = ans.readInt(-1000000000, 1000000000);
            int actual = ouf.readInt(-1000000000, 1000000000);
            if (actual != expected)
                quitf(_wa, "Test %d, query %d: expected %d, found %d", test, i + 1, expected, actual);
        }
    }
    if (!ans.seekEof()) quitf(_fail, "Extra tokens in jury answer");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "All %d answers match", query_number);
}
