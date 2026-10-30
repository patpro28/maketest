/*
Author: Tu Pham Anh
Date: 2026/10/30 - 10:21
*/
#include <bits/stdc++.h>

using namespace std;

const int N = 101;

int a[N][N], n, m;

void sub1() {
    for (int i = 1; i <= n; ++i) {
        int s = 0;
        for (int j = 1; j <= n; ++j)
            s += a[i][j];
        cout << s << ' ';
    }
}

void sub2() {
    cout << n << '\n';
    for (int i = 1; i <= n; ++i) {
        cout << count(a[i] + 1, a[i] + n + 1, 1) << ' ';
        for (int j = 1; j <= n; ++j)
            if (a[i][j]) cout << j << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    // freopen("DT.INP", "r", stdin);
    // freopen("DT.OUT", "w", stdout);
    
    int t; cin >> t;
    cin >> n; m = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j], m += a[i][j];

    if (t == 1) sub1();
    else sub2();

    return 0;
}