/*
Author: Tu Pham Anh
Date: 2025/10/04 - 17:26
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
    int a, b, c, d;
    cin >> s;
    cin >> a >> b >> c >> d;
    vector<char> t;
    for (char c = 'a'; c <= 'z'; c++)
        if (!count(s.begin(), s.end(), c))
            t.push_back(c);
    t.resize(4);
    cout << t[a - 1] << t[b - 1] << t[c - 1] << t[d - 1] << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}