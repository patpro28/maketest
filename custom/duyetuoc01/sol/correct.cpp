/*
Author: Tu Pham Anh
Date: 2025/03/11 - 21:08
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

pair<long long, long long> divisor(long long n) {
    long long sum_odd = 0, cnt_even = 0;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                cnt_even++;
            } else {
                sum_odd += i;
            }
            if (i * i != n) {
                long long j = n / i;
                if (j % 2 == 0) {
                    cnt_even++;
                } else {
                    sum_odd += j;
                }
            }
        }
    }
    return {cnt_even, sum_odd};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    long long n;
    cin >> n;
    auto [cnt, sum] = divisor(n);
    cout << cnt << "\n" << sum << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}