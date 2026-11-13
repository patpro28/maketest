#include <string>
#include "testlib.h"
#include "params.h"
using namespace std;

int main(int argc, char** argv) {
    registerValidation(argc, argv);
    int t = inf.readInt(1, T_MAX, "t");
    inf.readEoln();
    for (int tc = 0; tc < t; ++tc) {
        string s = inf.readToken("[a-z]{1,500}", "S");
        inf.readEoln();
        int state[26];
        fill(state, state + 26, 0);
        for (int i = 0; i < (int)s.size();) {
            int j = i + 1;
            while (j < (int)s.size() && s[j] == s[i]) ++j;
            int len = j - i, c = s[i] - 'a';
            ensuref(len <= 2, "Consecutive identical key presses in case %d", tc + 1);
            ensuref(state[c] == 0 || state[c] == len,
                    "Key state changes in case %d", tc + 1);
            state[c] = len;
            i = j;
        }
    }
    inf.readEof();
}
