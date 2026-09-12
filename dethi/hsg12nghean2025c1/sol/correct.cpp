/*
Author: Tu Pham Anh
Date: 2025/10/11 - 14:44
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
    long long a, b, N;
    cin >> a >> b >> N;
    // Find Nth natural number that is not divisible by a or b
    long long l = 1, r = 2e18;
    while (l < r) {
        long long mid = l + (r - l) / 2;
        long long cnt = mid - mid / a - mid / b + mid / (a / __gcd(a, b) * b);
        if (cnt < N) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}