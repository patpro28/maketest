/*
Author: Tu Pham Anh
Date: 2024/10/23 - 21:59
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

const int MAX = 1e6;

int cntA[2 * MAX + 1], cntB[2 * MAX + 1];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int x, i = 0; i < n; ++i)
        cin >> x, ++cntA[x + MAX];
    for (int x, i = 0; i < n; ++i)
        cin >> x, ++cntB[x + MAX];
    sort(cntA, cntA + 2 * MAX + 1);
    sort(cntB, cntB + 2 * MAX + 1);

    while (q--) {
        int k;
        cin >> k;
        auto posA = lower_bound(cntA, cntA + 2 * MAX + 1, k) - cntA;
        auto posB = lower_bound(cntB, cntB + 2 * MAX + 1, k) - cntB;
        cout << 2 * MAX - posA + 1 << ' ' << 2 * MAX - posB + 1 << '\n';
    }
    return 0;
}