#include "testlib.h"

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int q = inf.readInt();
    for (int i = 1; i <= q; ++i) {
        int expected = ans.readInt(0, n);
        int actual = ouf.readInt(0, n);
        if (actual != expected)
            quitf(_wa, "Query %d: expected %d, found %d", i, expected, actual);
    }
    if (!ans.seekEof()) quitf(_fail, "Extra tokens in jury answer");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "All %d answers match", q);
}
