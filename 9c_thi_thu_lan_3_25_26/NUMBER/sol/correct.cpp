/*
Author: Tu Pham Anh
Date: 2026/05/09 - 14:00
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int t; cin >> t;
    while (t--) {
        long long l, r; cin >> l >> r;
        cout << r / 4 - (l - 1) / 4 << "\n";
    }
    return 0;
}
