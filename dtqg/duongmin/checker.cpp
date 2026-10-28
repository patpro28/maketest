#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int count = 1;
    inf.readInt(); count = inf.readInt();
    for (int i = 0; i < count; ++i) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        if (expected != actual) quitf(_wa, "Answer %d: expected %lld, found %lld", i+1, expected, actual);
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "All answers match");
}
