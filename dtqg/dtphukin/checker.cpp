#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);

    int tests = inf.readInt();
    for (int i = 1; i <= tests; ++i) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        if (actual != expected) {
            quitf(_wa, "Test %d: expected %lld, got %lld", i, expected, actual);
        }
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d correct answers", tests);
}
