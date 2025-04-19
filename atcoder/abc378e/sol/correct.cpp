/*
Author: Tu Pham Anh
Date: 2024/11/02 - 19:51
*/
#include <bits/stdc++.h>
#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

using namespace std;

vector<int> bit;

void add(int i) {
    for (; i < (int)bit.size(); i += (i + 1) & -(i + 1)) 
        bit[i]++;
}

int get(int i) {
    int cnt = 0;
    for (; i >= 0; i -= (i + 1) & -(i + 1)) 
        cnt += bit[i];
    return cnt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    bit.resize(m);
    long long sum = 0, x;
    long long all = 0, ans = 0;
    add(0);
    for (int i = 0; i < n; ++i) {
        cin >> x;
        (sum += x) %= m;
        long long cnt = get(m - sum - 1);
        ans += sum * (i + 1) + all - (i + 1 - cnt) * m;
        all += (m - sum) % m;
        add((m - sum) % m);
    }
    cout << ans << '\n';

    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
    return 0;
}