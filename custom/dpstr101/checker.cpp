#include <algorithm>
#include <string>
#include "testlib.h"
bool subsequence(const std::string &small, const std::string &large) {
    size_t j = 0;
    for (char c : large) if (j < small.size() && small[j] == c) ++j;
    return j == small.size();
}
int main(int argc, char **argv) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), m = inf.readInt();
    std::string a = inf.readToken(), b = inf.readToken();
    int optimum = ans.readInt(0, std::min(n,m));
    int length = ouf.readInt(0, std::min(n,m), "length");
    std::string result = length ? ouf.readToken("[a-z]+", "subsequence") : "";
    if (int(result.size()) != length) quitf(_wa, "Incorrect output length");
    if (!subsequence(result,a) || !subsequence(result,b)) quitf(_wa, "Not a common subsequence");
    if (length < optimum) quitf(_wa, "Not optimal");
    if (length > optimum) quitf(_fail, "A better solution than the jury answer was found");
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "Valid longest common subsequence");
}
