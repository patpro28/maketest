#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int query = 0;
    while (!ans.seekEof()) {
        ++query;
        int expected = ans.readInt();
        int actual = ouf.readInt();
        if (actual != expected) {
            quitf(_wa, "Query %d: expected %d, found %d", query, expected, actual);
        }
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output after %d answers", query);
    quitf(_ok, "%d answers", query);
}
