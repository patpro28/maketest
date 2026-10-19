#include "testlib.h"

int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int expected = ans.readInt(0, 1000000006);
    int actual = ouf.readInt(0, 1000000006);
    if (actual != expected) quitf(_wa, "Expected %d, found %d", expected, actual);
    if (!ans.seekEof()) quitf(_fail, "Extra tokens in jury answer");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer matches");
}
