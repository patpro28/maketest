/*
Author: Tu Pham Anh
Date: 2026/05/22 - 17:39
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    getline(cin, s);
    map<char, int> freq;
    for (char c : s) {
        if (isalpha(c)) {
            freq[tolower(c)]++;
        }
    }
    for (auto &p : freq) {
        cout << p.first << " " << p.second << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}