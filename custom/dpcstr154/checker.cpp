#include <algorithm>
#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    int expected = ans.readInt(0, std::min(n, m));
    int actual = ouf.readInt(0, std::min(n, m), "answer");
    if (actual != expected) quitf(_wa, "Expected %d, found %d", expected, actual);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer matches");
}
