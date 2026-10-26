#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int count = 0;
    while (!ans.seekEof()) {
        std::string expected = ans.readToken(), actual = ouf.readToken();
        if (actual != expected) quitf(_wa, "Wrong verdict at token %d", count + 1);
        ++count;
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d output tokens match", count);
}
