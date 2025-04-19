/*
Author: Tu Pham Anh
Date: 2025/04/15 - 20:09
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
    cin >> s;
    int cntS[3] = {0, 0, 0};
    for (char c : s) {
        if (c == 'D') cntS[0]++;
        else if (c == 'V') cntS[1]++;
        else cntS[2]++;
    }
    int q, dem = 0;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int cnt[3] = {0, 0, 0};
        for (char c : t) {
            if (c == 'D') cnt[0]++;
            else if (c == 'V') cnt[1]++;
            else cnt[2]++;
        }
        if (cnt[0] + cntS[0] == cnt[1] + cntS[1] && cnt[1] + cntS[1] == cnt[2] + cntS[2]) {
            dem++;
        }
    }
    cout << dem;
    // cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}