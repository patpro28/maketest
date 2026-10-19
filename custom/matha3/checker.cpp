#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int tokens = 0;
    while (!ans.seekEof()) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        ++tokens;
        if (actual != expected) quitf(_wa, "Token %d: expected %lld, found %lld", tokens, expected, actual);
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d tokens match", tokens);
}
