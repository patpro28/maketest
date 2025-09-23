/*
Author: Tu Pham Anh
Date: 2025/07/25 - 18:22
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

struct PS {
    long long tu, mau;

    bool operator<(const PS &other) const {
        return tu * other.mau < mau * other.tu;
    }
} a[100005];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].tu >> a[i].mau;
        int g = __gcd(a[i].tu, a[i].mau);
        a[i].tu /= g;
        a[i].mau /= g;
    }
    sort(a, a + n);
    for (int i = 0; i < n; ++i) {
        cout << a[i].tu << " " << a[i].mau << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}