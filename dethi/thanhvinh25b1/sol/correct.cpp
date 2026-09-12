/*
Author: Tu Pham Anh
Date: 2025/10/15 - 18:07
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
    
    string a, b;
    cin >> a >> b;
    long long amin = 0, amax = 0, bmin = 0, bmax = 0;
    for (char c : a) {
        if (c == '5' || c == '6') {
            amin = amin * 10 + 5;
            amax = amax * 10 + 6;
        } else {
            amin = amin * 10 + (c - '0');
            amax = amax * 10 + (c - '0');
        }
    }

    for (char c : b) {
        if (c == '5' || c == '6') {
            bmin = bmin * 10 + 5;
            bmax = bmax * 10 + 6;
        } else {
            bmin = bmin * 10 + (c - '0');
            bmax = bmax * 10 + (c - '0');
        }
    }
    long long s1 = amin + bmin;
    long long s2 = amax + bmax;
    cout << min(s1, s2) << " " << max(s1, s2) << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}