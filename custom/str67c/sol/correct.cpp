#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        bool good[26] = {};
        for (int i = 0; i < (int)s.size();) {
            int j = i + 1;
            while (j < (int)s.size() && s[j] == s[i]) ++j;
            if (j - i == 1) good[s[i] - 'a'] = true;
            i = j;
        }
        for (int c = 0; c < 26; ++c)
            if (good[c]) cout << char('a' + c);
        cout << '\n';
    }
}
