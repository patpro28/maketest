/*
Author: Tu Pham Anh
Date: 2026/05/20 - 20:39
*/
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int t; cin >> t;
    while (t--) {
        int a, b;
        long long n;
        cin >> a >> b >> n;
        cout << (n / a) + (n / b) - n / lcm(a, b) << "\n";
    }

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}