#include "testlib.h"
#include <string>
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt(), s = inf.readInt();
    vector<int> a(n), b(n);
    vector<bool> reachable(s + 1, false);
    reachable[0] = true;
    for (int i = 0; i < n; ++i) {
        a[i] = inf.readInt(); b[i] = inf.readInt();
        vector<bool> next(s + 1, false);
        for (int t = 0; t <= s; ++t) if (reachable[t]) {
            if (t + a[i] <= s) next[t + a[i]] = true;
            if (t + b[i] <= s) next[t + b[i]] = true;
        }
        reachable.swap(next);
    }
    // Validate both jury and contestant certificates independently.
    auto validate = [&](InStream& stream, bool jury) {
        auto verdict = jury ? _fail : _wa;
        string status = stream.readToken();
        if (status == "No") {
            if (reachable[s]) quitf(verdict, "A valid arrangement exists");
        } else if (status == "Yes") {
            string choices = stream.readToken();
            if ((int)choices.size() != n) quitf(verdict, "Expected %d choices", n);
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                if (choices[i] == 'A') sum += a[i];
                else if (choices[i] == 'B') sum += b[i];
                else quitf(verdict, "Only A and B are allowed");
            }
            if (sum != s) quitf(verdict, "Expected sum %d, found %d", s, sum);
        } else quitf(verdict, "Expected Yes or No");
        if (!stream.seekEof()) quitf(verdict, "Extra output");
    };
    validate(ans, true);
    validate(ouf, false);
    quitf(_ok, "Valid answer");
}
