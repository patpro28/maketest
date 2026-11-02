#include "testlib.h"
#include <string>
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    std::string first = ans.readToken();
    if (first == "NONE") {
        if (ouf.readToken() != "NONE") quitf(_wa, "Expected NONE");
    } else {
        long long expected = std::stoll(first), actual = ouf.readLong();
        if (actual != expected) quitf(_wa, "Wrong best sum");
        int position = ans.readInt();
        if (ouf.readInt() != position) quitf(_wa, "Wrong earliest position");
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Answer matches");
}
