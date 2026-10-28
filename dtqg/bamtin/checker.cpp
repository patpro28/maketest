#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    long long expected = ans.readLong();
    long long actual = ouf.readLong();
    if (expected != actual) quitf(_wa, "Expected %lld, found %lld", expected, actual);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer matches");
}
