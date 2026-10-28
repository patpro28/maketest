#include "testlib.h"
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int count = 1;
    int n = inf.readInt(), q = inf.readInt();
    for (int i = 0; i < n; ++i) inf.readInt();
    count = 0;
    for (int i = 0; i < q; ++i) {
        std::string op = inf.readToken();
        if (op == "?") ++count;
        else { inf.readInt(); inf.readInt(); }
    }
    for (int i = 0; i < count; ++i) {
        long long expected = ans.readLong();
        long long actual = ouf.readLong();
        if (actual != expected)
            quitf(_wa, "Answer %d: expected %lld, found %lld", i + 1, expected, actual);
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "All answers match");
}
