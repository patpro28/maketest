#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int i = 1; i <= t; ++i) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong(-1LL, 2999980000LL, "answer");
        if (actual != expected)
            quitf(_wa, "Case %d: expected %lld, found %lld", i, expected, actual);
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d answers", t);
}
