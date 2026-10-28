#include "testlib.h"
#include <string>
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int tokens = 0;
    while (!ans.seekEof()) {
        std::string expected = ans.readToken();
        if (expected.size() == 1 && expected[0] >= 'a' && expected[0] <= 'z') {
            std::string actual = ouf.readToken();
            if (actual != expected) quitf(_wa, "Wrong character at token %d", tokens + 1);
        } else {
            long long actual = ouf.readLong();
            if (actual != std::stoll(expected)) quitf(_wa, "Wrong integer at token %d", tokens + 1);
        }
        ++tokens;
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d tokens match", tokens);
}
