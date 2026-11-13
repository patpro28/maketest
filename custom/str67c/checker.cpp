#include <string>
#include "testlib.h"
using namespace std;

string trimLine(string s) {
    size_t first = s.find_first_not_of(" \t\r");
    if (first == string::npos) return "";
    size_t last = s.find_last_not_of(" \t\r");
    return s.substr(first, last - first + 1);
}

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int t = inf.readInt();
    for (int tc = 1; tc <= t; ++tc) {
        string s = inf.readToken();
        bool good[26] = {};
        for (int i = 0; i < (int)s.size(); ++i)
            if ((i == 0 || s[i - 1] != s[i]) &&
                (i + 1 == (int)s.size() || s[i + 1] != s[i]))
                good[s[i] - 'a'] = true;
        string expected;
        for (int c = 0; c < 26; ++c)
            if (good[c]) expected += char('a' + c);

        if (ans.eof()) quitf(_fail, "Missing answer line %d", tc);
        if (trimLine(ans.readLine()) != expected)
            quitf(_fail, "Incorrect answer at case %d", tc);
        if (ouf.eof()) quitf(_wa, "Missing output line %d", tc);
        string actual = trimLine(ouf.readLine());
        if (actual != expected)
            quitf(_wa, "Case %d: expected '%s', found '%s'",
                  tc, expected.c_str(), compress(actual).c_str());
    }
    if (!ans.seekEof()) quitf(_fail, "Extra answer data");
    if (!ouf.seekEof()) quitf(_wa, "Extra output data");
    quitf(_ok, "%d cases", t);
}
