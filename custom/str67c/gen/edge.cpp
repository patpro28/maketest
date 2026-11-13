#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int, char** argv) {
    int seed = atoi(argv[1]);
    vector<string> cases;
    if (seed == 0) {
        for (char c = 'a'; c <= 'z'; ++c) {
            cases.push_back(string(1, c));
            cases.push_back(string(2, c));
        }
    } else if (seed == 1) {
        cases = {"ababa", "bbaabb", "cbddb", "zazaz", "a", "zz", "z", "aa"};
    } else if (seed == 2) {
        string asc, desc, doubled;
        for (char c = 'a'; c <= 'z'; ++c) asc += c;
        for (char c = 'z'; c >= 'a'; --c) desc += c;
        for (char c : desc) doubled += string(2, c);
        cases = {asc, desc, doubled, asc + desc.substr(1)};
    } else {
        for (int tc = 0; tc < 100; ++tc) {
            string s;
            if (seed == 3) {
                for (int i = 0; i < 500; ++i) s += char('a' + (i + tc) % 26);
            } else if (seed == 4) {
                for (int i = 0; i < 250; ++i) s += string(2, char('a' + (i + tc) % 26));
            } else {
                s = string(1, char('a' + tc % 26));
                while (s.size() + 3 <= 500) {
                    s += string(2, char('a' + (tc + 1) % 26));
                    s += char('a' + tc % 26);
                }
            }
            cases.push_back(s);
        }
    }
    cout << cases.size() << '\n';
    for (const string& s : cases) cout << s << '\n';
}
