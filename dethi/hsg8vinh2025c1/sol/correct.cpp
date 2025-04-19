/*
Author: Tu Pham Anh
Date: 2025/04/15 - 18:36
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s; cin >> s;
    int sum = 0;
    for (char c : s) 
        if (c != 'X') sum += c - '0';
    for (int i = 9; i >= 0; --i)
        if (isPrime(sum + i)) {
            s[s.find('X')] = i + '0';
            cout << s;
            return 0;
        }
    cout << -1;
    // cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}