#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int count = 0;
    while (!ans.seekEof()) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        ++count;
        if (actual != expected) {
            quitf(_wa, "Integer %d: expected %lld, found %lld", count, expected, actual);
        }
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output after %d integers", count);
    quitf(_ok, "%d integers match", count);
}
