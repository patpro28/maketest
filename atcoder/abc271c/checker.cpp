#include "testlib.h"
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int expected = ans.readInt(0, 300000);
    int actual = ouf.readInt(0, 300000);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    if (actual != expected) quitf(_wa, "Expected %d, found %d", expected, actual);
    quitf(_ok, "Answer is %d", actual);
}
