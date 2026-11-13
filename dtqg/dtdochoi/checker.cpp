#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    const int expected = ans.readInt();
    const int actual = ouf.readInt();
    if (actual != expected) quitf(_wa, "Expected %d, found %d", expected, actual);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer: %d", actual);
}
