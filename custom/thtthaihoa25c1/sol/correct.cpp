/*
Author: Tu Pham Anh
Date: 2025/04/20 - 12:04
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
    map<char, char> op = { {'S', 'N'}, {'N', 'S'}, {'E', 'W'}, {'W', 'E'} };
    string s; cin >> s;
    for (auto c : s) 
        cout << op[c];

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}