#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    for (int i = 0; i < 1; ++i) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        if (actual != expected)
            quitf(_wa, "Token %d: expected %lld, found %lld", i + 1, expected, actual);
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer matches");
}
