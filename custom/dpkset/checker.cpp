#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    long long expected = ans.readLong();
    int count = ans.readInt();
    long long actual = ouf.readLong(-9900000000000LL, 9900000000000LL, "weight");
    int ways = ouf.readInt(0, 1000000006, "count");
    if (actual != expected || ways != count)
        quitf(_wa, "Expected %lld %d, found %lld %d", expected, count, actual, ways);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Weight and count match");
}
