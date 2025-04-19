#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

vector<int> f, a;

int n, d;

void calLIS() {
    vector<int> b;
    for (int i = 1; i <= n; i++) {
        auto it = lower_bound(b.begin(), b.end(), a[i]);
        if (it == b.end()) {
            b.push_back(a[i]);
            f[i] = b.size();
        } else {
            *it = a[i];
            f[i] = it - b.begin() + 1;
        }
    }
    d = b.size();
}

void solve() {
    vector<deque<pair<int, long long>>> sl(d + 1);
    vector<long long> sum(d + 1);
    sum[0] = 1;

    for (int i = 1; i <= n; i++) {
        int k = f[i] - 1;
        while (!sl[k].empty() && sl[k].front().first >= a[i]) {
            auto [_, s] = sl[k].front();
            sl[k].pop_front();
            sum[k] = (sum[k] - s) % MOD;
        }
        sl[k + 1].push_back({a[i], sum[k]});
        sum[k + 1] = (sum[k + 1] + sum[k]) % MOD;
    }
    cout << (sum[d] + MOD) % MOD << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    cin >> n;
    f.resize(n + 1);
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    calLIS();
    solve();
    
    return 0;
}
