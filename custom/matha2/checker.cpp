#include "testlib.h"

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int i = 1; i <= t; ++i) {
        long long expected = ans.readLong(0LL, 1000000000000000000LL);
        long long actual = ouf.readLong(0LL, 1000000000000000000LL);
        if (actual != expected)
            quitf(_wa, "Case %d: expected %lld, found %lld", i, expected, actual);
    }
    if (!ans.seekEof()) quitf(_fail, "Extra tokens in jury answer");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "All %d answers match", t);
}
